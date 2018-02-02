/* inih -- simple .INI file parser

inih is released under the New BSD license (see LICENSE.txt). Go to the project
home page for more info:

https://github.com/benhoyt/inih

*/

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <windows.h>
#include "ini.h"

#define MAX_SECTION 50
#define MAX_NAME 50

/* Used by ini_parse_string() to keep track of string parsing state. */
typedef struct {
    const char* ptr;
    size_t num_left;
} ini_parse_string_ctx;

/* Strip whitespace chars off end of given string, in place. Return s. */
static char* rstrip(char* s)
{
    char* p = s + strlen(s);
    while (p > s && isspace((unsigned char)(*--p)))
        *p = '\0';
    return s;
}

/* Return pointer to first non-whitespace char in given string. */
static char* lskip(const char* s)
{
    while (*s && isspace((unsigned char)(*s)))
        s++;
    return (char*)s;
}

/* Return pointer to first char (of chars) or inline comment in given string,
   or pointer to null at end of string if neither found. Inline comment must
   be prefixed by a whitespace character to register as a comment. */
static char* find_chars_or_comment(const char* s, const char* chars)
{
#if INI_ALLOW_INLINE_COMMENTS
    int was_space = 0;
    while (*s && (!chars || !strchr(chars, *s)) &&
           !(was_space && strchr(INI_INLINE_COMMENT_PREFIXES, *s))) {
        was_space = isspace((unsigned char)(*s));
        s++;
    }
#else
    while (*s && (!chars || !strchr(chars, *s))) {
        s++;
    }
#endif
    return (char*)s;
}

/* Version of strncpy that ensures dest (size bytes) is null-terminated. */
static char* strncpy0(char* dest, const char* src, size_t size)
{
    strncpy(dest, src, size);
    dest[size - 1] = '\0';
    return dest;
}
/* get next line from input data */
static int reader(char *line, char*data, int data_len)
{
	static int pos = 0;
	int lpos = 0;
	//static char line[1024];
	if (pos >= data_len) return NULL;
	while ((pos < data_len) && (data[pos] != 0x0D)) {
		line[lpos++] = data[pos++];
	}
  pos++;
  pos++;
  line[lpos] = 0;
  
  return lpos;
}

/**************************************************************/
/**************************************************************/

ini_handler handler; /* pointer to handler function */
char *data = NULL; /* file buffer */
int data_len; /* length of file */
char line[INI_MAX_LINE];  /* line buffer */
HANDLE hheap;  /* process heap handle */
HANDLE hfile; /* file handle */

int ini_set_handler(ini_handler hnd)
{
	handler = hnd;
	return 0;
}

int ini_read(char *filename)
{
	ini_data_init();
	ini_load(filename);
	//MessageBoxA(NULL, "soubor načten", "last error", MB_OK);
	ini_parse();
	//MessageBoxA(NULL, "soubor zpracován", "last error", MB_OK);
	ini_data_destroy();
	//
}

int ini_data_init(void)
{
	/* initialize buffers */
	hheap = GetProcessHeap();
  if (hheap == NULL) return -2;
  data = HeapAlloc(hheap, HEAP_ZERO_MEMORY, INI_MAX_SIZE);
  if (data == NULL) return -3;
}

void ini_data_destroy(void)
{
	HeapFree(hheap, 0, (LPVOID) data);
}

int ini_load(char *filename)
{
const char data_default = 
	"[generic]\n"
	"testmode=0\n"
	"[serial]\n"
	"port=4\n"
	"baud=115200\n"
	"[rcs]\n"
	"allvisible=0\n"
	"modules=1,3,4,5\n"
	"\n";
	/* load file to RAM */
  //MessageBoxA(NULL, "open cfg file", "debug", MB_OK);
  hfile = CreateFileW(u"rcs\\XpressNET_acc.ini",
                      GENERIC_READ,          // open for writing
                      FILE_SHARE_READ | FILE_SHARE_WRITE,                      // do not share
                      NULL,                   // default security
                      OPEN_ALWAYS,            // ...
                      FILE_ATTRIBUTE_NORMAL,  // normal file
                      NULL);                  // no attr. template
  if (hfile == INVALID_HANDLE_VALUE) {
  	MessageBoxW(NULL, u"nejde otevřít (ani vytvořit) soubor s konfigurací", u"error", MB_OK);
	  return -1;
	}
  
		char dbgg[22];
		int gg;
		gg = GetLastError();
//	  itoa(dbgg, gg, 10);                      
//    MessageBoxA(NULL, dbgg, "last error", MB_OK);   



  /*if (GetLastError() == 0) {*/
  if (gg == 0) {
		/* config file don't exist */
		/* write default */
		WriteFile(hfile,
		          data_default,
							sizeof(data_default),
							&gg,
							NULL);
							
	  /*itoa(hfile, dbgg, gg);*/                      
    /*MessageBoxA(NULL, "default config created.", "debug", MB_OK);*/
	}
  
  /*MessageBoxA(NULL, data, "ready to load cfg", MB_OK);*/
  ReadFile(hfile,
           data,
           INI_MAX_SIZE,  // DWORD        nNumberOfBytesToRead,
           &data_len,     // LPDWORD      lpNumberOfBytesReaded,
           NULL           // LPOVERLAPPED lpOverlapped
  );
  
  //data_len = INI_MAX_SIZE;
  /*
  char fff[64];
  for(int i = 0; i<7; i++) { 
    fff[i] = ((data_len >> ((7-i)*4)) & 0x000f); fff[i] += (fff[i] > 9) ? 'A'-10 : '0';
  }
  fff[8] = 0;
  fff[9] = 0;
  MessageBoxA(NULL, fff, "loaded cfg", MB_OK);
  */
  CloseHandle(hfile);
  return 0;
}

/* See documentation in header file. */
int ini_parse()
{
	void *user = NULL;
    /* Uses a fair bit of stack (use heap instead if you need to) */
#if INI_USE_STACK
    char line[INI_MAX_LINE];
#else
    char* line;
#endif
    char section[MAX_SECTION] = "";
    char prev_name[MAX_NAME] = "";

    char* start;
    char* end;
    char* name;
    char* value;
    int lineno = 0;
    int error = 0;

#if !INI_USE_STACK
    line = (char*)malloc(INI_MAX_LINE);
    if (!line) {
        return -2;
    }
#endif

#define HANDLER(u, s, n, v) handler(u, s, n, v)

    /* Scan through stream line by line */
    while (reader(line, data, data_len) != NULL) {
        lineno++;

        start = line;
        /*
#if INI_ALLOW_BOM
        if (lineno == 1 && (unsigned char)start[0] == 0xEF &&
                           (unsigned char)start[1] == 0xBB &&
                           (unsigned char)start[2] == 0xBF) {
            start += 3;
        }
#endif
*/
        start = lskip(rstrip(start));
        
        if (*start == ';' || *start == '#') {
            /* Per Python configparser, allow both ; and # comments at the
               start of a line */
        }
#if INI_ALLOW_MULTILINE
        else if (*prev_name && *start && start > line) {
            /* Non-blank line with leading whitespace, treat as continuation
               of previous name's value (as per Python configparser). */
            if (!HANDLER(user, section, prev_name, start) && !error)
                error = lineno;
        }
#endif
        else if (*start == '[') {
            /* A "[section]" line */
            end = find_chars_or_comment(start + 1, "]");
            if (*end == ']') {
                *end = '\0';
                strncpy0(section, start + 1, sizeof(section));
                *prev_name = '\0';
            }
            else if (!error) {
                /* No ']' found on section line */
                error = lineno;
            }
        }
        else if (*start) {
            /* Not a comment, must be a name[=:]value pair */
            end = find_chars_or_comment(start, "=:");
            if (*end == '=' || *end == ':') {
                *end = '\0';
                name = rstrip(start);
                value = end + 1;
#if INI_ALLOW_INLINE_COMMENTS
                end = find_chars_or_comment(value, NULL);
                if (*end)
                    *end = '\0';
#endif
                value = lskip(value);
                rstrip(value);

                /* Valid name[=:]value pair found, call handler */
                strncpy0(prev_name, name, sizeof(prev_name));
                if (!HANDLER(user, section, name, value) && !error)
                    error = lineno;
            }
            else if (!error) {
                /* No '=' or ':' found on name[=:]value line */
                error = lineno;
            }
        }

#if INI_STOP_ON_FIRST_ERROR
        if (error)
            break;
#endif
    }

#if !INI_USE_STACK
    free(line);
#endif

    return error;
}

