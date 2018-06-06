/* ========================================================================== */
/*                                                                            */
/*   config.c                                                                 */
/*   (c) 2017 Michal Petrilak                                                 */
/*                                                                            */
/*   Load configuration variables from ini file                               */
/*                                                                            */
/* ========================================================================== */

#include "ini.h"
#include "config.h"
#include <string.h>

struct scfg *cfg;
HANDLE hheap = NULL;  /* process heap handle */

int cfg_load(void)
{
  int i;
  
	/* init memory */
  hheap = GetProcessHeap();
  if (hheap == NULL) return -2;
	if (cfg != NULL) {
		/* dealoc mem */
		HeapFree(hheap, 0, (LPVOID) cfg);
	}
  cfg = HeapAlloc(hheap, HEAP_ZERO_MEMORY, sizeof(struct scfg));
  if (cfg == NULL) return -3;	
  /* init memory */
  for(i=0; i<128; i++) {
    cfg->busi.mod[i].active = 0;
    wcscpy(cfg->busi.mod[i].name, u"");
    wcscpy(cfg->busi.mod[i].fw, u"");
  }
  
	/* load ini file */
	ini_set_handler(inihandler);
	ini_read(L"test.ini");
	return;
}

#define MATCH(s, n) ((strcmp(section, s) == 0) && (strcmp(name, n) == 0))


// ini config parser handler
static int inihandler(void* user, const char* section, const char* name,
                   const char* value)
{
    struct Tconfig *pconfig = (struct Tconfig*)user;
    int i;
    char str[64];

    if (MATCH("second_li", "port")) {
      int i;
      //mbstowcs(cfg->port_name, value, 32);
      MultiByteToWideChar(CP_ACP, 0, value, -1, cfg->port_name, 32);
      return 1;
    }
    //strcpy(cfg->port_name, value);
    if (MATCH("second_li", "baud")) {
        cfg->port_baud = atoi(value);
        return 1;
    }
    if (MATCH("bus_in", "count")) {
        cfg->busi.module_count = atoi(value);
        return 1;
    }
    for(i=0; i<128; i++) {
           
      /* check for every possible board */
      sprintf(str, "mod%.3d_active", i);
      if (MATCH("bus_in", str)) {
        cfg->busi.mod[i].active = atoi(value);
        return 1;
      }
      sprintf(str, "mod%.3d_name", i);
      if (MATCH("bus_in", str)) {
        sprintf(str, "%s\n%d\n", value, i);
        //MessageBoxA(NULL, str, "dbg", MB_OK);
        MultiByteToWideChar(CP_ACP, 0, value, -1, cfg->busi.mod[i].name, 64);
        //MessageBoxW(NULL, cfg->busi.mod[i].name, u"dbg", MB_OK);
        return 1;
      }
      sprintf(str, "mod%d.3_fw", i);
      if (MATCH("bus_in", str)) {
        MultiByteToWideChar(CP_ACP, 0, value, -1, cfg->busi.mod[i].fw, 64);
        return 1;
      }

    }
    // add custom config parsers
    
    
    return 0;  /* unknown section/name, error */
    
}