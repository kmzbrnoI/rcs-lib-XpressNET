/*********************************************************
*  XpressNET libraly for Accesories                      *
*   usable witch hJOP software                           *
*                                                        *
*                                                        *
*********************************************************/

#include <Windows.h>

#include "errors.h"
#include "LibraryEvents.h"
#include "XpressNet_acc.h"
#include "ConfigDialog.h"
#include "ini.h"

int g_initialized = 0;
unsigned int g_loglevel = 0;
int g_started = 0;
int g_opened = 0;
HANDLE g_ConfigThread;

struct Tconfig {
  WCHAR portname[32];
  int baudspeed;
  // add custom config variables
} g_config = { L"", 0 };

union Tout {
  unsigned short int bytes[128];
  struct Tout_bits {
    int out0: 1;
    int out1: 1;
    int out2: 1;
    int out3: 1;
    int out4: 1;
    int out5: 1;
    int out6: 1;
    int out7: 1;
  } bits[128];
} outs;

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpReserved )  // reserved
{
  // init
  
  // test outpus status reading
  outs.bits[5].out2 = 1;
  g_ConfigThread = CreateThread(NULL, 0, ConfigThreadFunc, NULL, 0, NULL);
  return 1; // Success
}


// ini config parser handler
static int inihandler(void* user, const char* section, const char* name,
                   const char* value)
{
    struct Tconfig *pconfig = (struct Tconfig*)user;

    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
    if (MATCH("second_li", "port")) {
        wcscpy(pconfig->portname, value);
    } else if (MATCH("second_li", "baud")) {
        pconfig->baudspeed = atoi(value);
    // add custom config parsers
    } else {
        return 0;  /* unknown section/name, error */
    }
    return 1;
}

//function LoadConfig(filename:PChar):Integer
int __stdcall XPRESSNET_LIB LoadConfig(char* filename) 
{
  // if opened, shall not pass
  if (g_opened) return MTB_FILE_DEVICE_OPENED;
/*
  HANDLE i;
  unsigned char confdata_raw[1024];
  i = CreateFileA(filename,
                 GENERIC_WRITE,           // open for writing
                 FILE_SHARE_READ,        // allow other readers
                 NULL,                   // default security
                 CREATE_NEW,             // create new file only
                 FILE_ATTRIBUTE_NORMAL,  // normal file
                 NULL);                  // no attr. template
  if (i == INVALID_HANDLE_VALUE) {
    // some error with config file
    return MTB_FILE_CANNOT_ACCESS;
  }
  // ToDo - read config
  
  // ToDo - parse config
  if (ini_parse_string(buf, inihandler, &g_config) < 0) {
    // error
    return MTB_FILE_CANNOT_ACCESS;
  }
  
  CloseHandle(i);
*/  
  
  
  return 0;
}

int __stdcall XPRESSNET_LIB SaveConfig(char* filename)
{
  HANDLE i;
  WCHAR buf = L"test\n";
  
  i = CreateFileW(L"out.ini",
                 GENERIC_WRITE,          // open for writing
                 0,                      // do not share
                 NULL,                   // default security
                 CREATE_NEW,             // create new file only
                 FILE_ATTRIBUTE_NORMAL,  // normal file
                 NULL);                  // no attr. template
  WriteFile(i,
            buf,
            10,     // DWORD        nNumberOfBytesToWrite,
            NULL,   // LPDWORD      lpNumberOfBytesWritten,
            NULL    // LPOVERLAPPED lpOverlapped
  );
  CloseHandle(i);
  return -1;
}

////////////////////////////////////////////////////////////////////////////////

void __stdcall XPRESSNET_LIB SetLogLevel(unsigned int loglevel)
{
  g_loglevel = loglevel;
}

unsigned int __stdcall XPRESSNET_LIB GetLogLevel(void)
{
  return g_loglevel;
}

////////////////////////////////////////////////////////////////////////////////

void __stdcall XPRESSNET_LIB ShowConfigDialog()
{
  HANDLE i;
  MessageBoxA(NULL, "XpressNET nemá žádné interaktivní nastavení,\nvše je v souboru \\rcs\\XpressNET.ini", "Není nastavení", MB_OK);
}

////////////////////////////////////////////////////////////////////////////////
// empty functions:
void __stdcall XPRESSNET_LIB HideConfigDialog()
{
  return;
}

int __stdcall XPRESSNET_LIB OpenDevice(char *device, bool persist)
{
  return 0;
}

int __stdcall XPRESSNET_LIB GetDeviceCount()
{
  return 1;
}

////////////////////////////////////////////////////////////////////////////////
// get versions
int __stdcall XPRESSNET_LIB GetDeviceVersion(char *version, unsigned int versionLen)
{
  wcscpy(version, L"N/A");
  return 0;
}
void __stdcall XPRESSNET_LIB GetDriverVersion(char *version, unsigned int versionLen)
{
  wcscpy(version, L"v 0.1");
  return;
}

////////////////////////////////////////////////////////////////////////////////
// get modules info
bool __stdcall XPRESSNET_LIB IsModule(unsigned int module)
{
  if (module < 128) {
    return -1;
   } else {
    return 0;      
  }
}

unsigned int __stdcall XPRESSNET_LIB GetModuleCount(void) {
  return 128;
}

int __stdcall XPRESSNET_LIB GetModuleName(unsigned int module, char *name, unsigned int nameLen)
{
  //
  if (module < 128) {
    wcscpy(name, L"RS-module");  
   } else {
    name[0] = 0;
    name[1] = 0; 
  }
  return 0;
}

int __stdcall XPRESSNET_LIB GetModuleFW(unsigned int module, char *fw, unsigned int fwLen)
{
  //
  if (module < 128) {
    wcscpy(fw, L"N/A");  
   } else {
    wcscpy(fw, L""); 
  }
  return 0;
}



////////////////////////////////////////////////////////////////////////////////

int __stdcall XPRESSNET_LIB Open()
{
  //
  if (g_opened) return MTB_ALREADY_OPENNED;
  if (LibEvents.BeforeOpen.event != NULL) LibEvents.BeforeOpen.event(NULL, LibEvents.BeforeOpen.data);
  //
  // ToDo: open serial port
  // return MTB_GENERAL_EXCEPTION;
  //
  g_opened = 1;
  if (LibEvents.AfterOpen.event != NULL) LibEvents.AfterOpen.event(NULL, LibEvents.AfterOpen.data);
  
  return 0;
}

int __stdcall XPRESSNET_LIB Close()
{
//
  if (!g_opened) return MTB_NOT_OPENED;
  // return MTB_SCANNING_NOT_FINISHED  // nikdy nemùže nastat
  if (LibEvents.BeforeClose.event != NULL) LibEvents.BeforeClose.event(NULL, LibEvents.BeforeClose.data);
  //
  // ToDo: close serial port
  // return MTB_GENERAL_EXCEPTION;
  //
  g_opened = 0;
  if (LibEvents.AfterClose.event != NULL) LibEvents.AfterClose.event(NULL, LibEvents.AfterClose.data);
  
  return 0;
}

bool __stdcall XPRESSNET_LIB Opened()
{
  return g_opened==1;
}

////////////////////////////////////////////////////////////////////////////////

int __stdcall XPRESSNET_LIB Start()
{
  int i;
  //
  if (g_started) return MTB_ALREADY_STARTED;
  if (LibEvents.BeforeStart.event != NULL) LibEvents.BeforeStart.event(NULL, LibEvents.BeforeStart.data);
  //
  // do nothing
  // return MTB_GENERAL_EXCEPTION;
  // return MTB_NO_MODULES;
  // return MTB_SCANNING_NOT_FINISHED;
  // return MTB_NOT_OPENED;
  //
  g_started = 1;
  if (LibEvents.AfterStart.event != NULL) LibEvents.AfterStart.event(NULL, LibEvents.AfterStart.data);
  
  // fake first scan
  if (LibEvents.OnInputChanged.event != NULL) {
    for( i = 0; i < 128; i++) {
       LibEvents.OnInputChanged.event(NULL, LibEvents.OnInputChanged.data, i);
    }
  }
  
  return 0;
}

int __stdcall XPRESSNET_LIB Stop()
{
  //
  if (!g_started) return MTB_NOT_STARTED;
  if (LibEvents.BeforeStop.event != NULL) LibEvents.BeforeStop.event(NULL, LibEvents.BeforeStop.data);
  //
  // do nothing
  // return MTB_GENERAL_EXCEPTION;
  //
  g_started = 0;
  if (LibEvents.AfterStop.event != NULL) LibEvents.AfterStop.event(NULL, LibEvents.AfterStop.data);
  
  return 0;
}

bool __stdcall XPRESSNET_LIB Started()
{
  return (g_started == 1);
}

////////////////////////////////////////////////////////////////////////////////

// ToDo:
int __stdcall XPRESSNET_LIB GetInput(unsigned int module, unsigned int port)
{
  int ret;
  
  if (module > 127) return MTB_MODULE_INVALID_ADDR;
  if (port   > 15)  return MTB_PORT_INVALID_NUMBER;
  if (port   > 7)   return 0;
  
  if (module   > 20)  return MTB_INPUT_NOT_YET_SCANNED;
  // MTB_INPUT_NOT_YET_SCANNED

  ret = ((module + port) % 3) == 0;
  return ret;
}

int __stdcall XPRESSNET_LIB GetOutput(unsigned int module, unsigned int port)
{
  if (module > 127) return MTB_MODULE_INVALID_ADDR; //MTB_MODULE_NOT_AVAILABLE;
  if (port   > 15)   return MTB_PORT_INVALID_NUMBER;
  if (port   > 7)   return 0;
  
  return (outs.bytes[module] >> port) & 1;
}

int __stdcall XPRESSNET_LIB SetOutput(unsigned int module, unsigned int port, int state)
{
  if (module > 127) return MTB_MODULE_INVALID_ADDR;
  if (port   > 15)   return MTB_PORT_INVALID_NUMBER;
  if (port   > 7)   return 0;
  
  if (state) {
    outs.bytes[module] |=  (1 << port);
   } else {
    outs.bytes[module] &= ~(1 << port);
  }
  return 0;
} 

////////////////////////////////////////////////////////////////////////////////

void __stdcall XPRESSNET_LIB GetDeviceSerial(int index, char *serial, unsigned int serialLen) {
  wcscpy(serial, L"--");
  return;
}

bool __stdcall XPRESSNET_LIB IsModuleFailure(unsigned int module) {
  // can't be detected :-(
  return 0;
}

int __stdcall XPRESSNET_LIB GetModuleType(unsigned int module)
{
//     idMTB_UNI = $40,
//     idMTB_UNIOUT = $50,
//     idMTB_TTL = $60,
//     idMTB_TTLOUT_ID = $70
  // can't be determined
  return 0x60; // UNI
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void __stdcall XPRESSNET_LIB BindBeforeOpen(TStdNotifyEvent *event, void *data)
{
  LibEvents.BeforeOpen.data  = data;
  LibEvents.BeforeOpen.event = event;
}

void __stdcall XPRESSNET_LIB BindAfterOpen(TStdNotifyEvent *event, void *data)
{
  LibEvents.AfterOpen.data  = data;
  LibEvents.AfterOpen.event = event;
}

void __stdcall XPRESSNET_LIB BindBeforeClose(TStdNotifyEvent *event, void *data)
{
  LibEvents.BeforeClose.data  = data;
  LibEvents.BeforeClose.event = event;
}

void __stdcall XPRESSNET_LIB BindAfterClose(TStdNotifyEvent *event, void *data)
{
  LibEvents.AfterClose.data  = data;
  LibEvents.AfterClose.event = event;
}

void __stdcall XPRESSNET_LIB BindBeforeStart(TStdNotifyEvent *event, void *data)
{
  LibEvents.BeforeStart.data  = data;
  LibEvents.BeforeStart.event = event;
}

void __stdcall XPRESSNET_LIB BindAfterStart(TStdNotifyEvent *event, void *data)
{
  LibEvents.AfterStart.data  = data;
  LibEvents.AfterStart.event = event;
}

void __stdcall XPRESSNET_LIB BindBeforeStop(TStdNotifyEvent *event, void *data)
{
  LibEvents.BeforeStop.data  = data;
  LibEvents.BeforeStop.event = event;
}

void __stdcall XPRESSNET_LIB BindAfterStop(TStdNotifyEvent *event, void *data)
{
  LibEvents.AfterStop.data  = data;
  LibEvents.AfterStop.event = event;
}

void __stdcall XPRESSNET_LIB BindOnError(TStdErrorEvent event, void *data)
{
  LibEvents.OnError.data  = data;
  LibEvents.OnError.event = event;
}

void __stdcall XPRESSNET_LIB BindOnLog(TStdLogEvent *event, void *data)
{
  LibEvents.OnLog.data  = data;
  LibEvents.OnLog.event = event;
}

void __stdcall XPRESSNET_LIB BindOnInputChanged(TStdModuleChangeEvent *event, void *data)
{
  LibEvents.OnInputChanged.data  = data;
  LibEvents.OnInputChanged.event = event;
}

void __stdcall XPRESSNET_LIB BindOnOutputChanged(TStdModuleChangeEvent *event, void *data)
{
  LibEvents.OnOutputChanged.data  = data;
  LibEvents.OnOutputChanged.event = event;
}

void __stdcall XPRESSNET_LIB BindOnScanned(TStdNotifyEvent *event, void *data)
{
  LibEvents.OnScanned.data  = data;
  LibEvents.OnScanned.event = event;
}

/*
TXpressNET::TXpressNET()
{
  ;
 
}

TXpressNET::~TXpressNET()
{
  ;
 
}
*/
