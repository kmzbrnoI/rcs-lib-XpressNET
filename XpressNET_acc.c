/*********************************************************
*  XpressNET libraly for Accesories                      *
*   usable witch hJOP software                           *
*                                                        *
*                                                        *
*********************************************************/

#include "Windows.h"
#include "XpressNet_acc.h"

unsigned int g_loglevel;
int g_started;
int g_opened;


//function LoadConfig(filename:PChar):Integer
int __stdcall XPRESSNET_LIB LoadConfig(char* filename) 
{
  return 0;
}

int __stdcall XPRESSNET_LIB SaveConfig(char* filename)
{
  HANDLE i;
  i = CreateFileA(filename,
                 GENERIC_WRITE,          // open for writing
                 0,                      // do not share
                 NULL,                   // default security
                 CREATE_NEW,             // create new file only
                 FILE_ATTRIBUTE_NORMAL,  // normal file
                 NULL);                  // no attr. template
  CloseHandle(i);
  return -1;
}

void __stdcall XPRESSNET_LIB SetLogLevel(unsigned int loglevel)
{
  g_loglevel = loglevel;
  return;
 
}

void __stdcall XPRESSNET_LIB ShowConfigDialog()
{
  //
  //#pragma comment(linker, "/EXPORT:"__FUNCTION__"="__FUNCDNAME__)

  HANDLE i;
  MessageBoxA(NULL, "XpressNET nemá žádné interaktivní nastavení,\nvše je v souboru \\rcs\\XpressNET.ini", "Není nastavení", MB_OK);
  return;
}

// empty functions:
void __stdcall XPRESSNET_LIB HideConfigDialog() {return;}
int __stdcall XPRESSNET_LIB Start() {g_started = 1; return 0;}
int __stdcall XPRESSNET_LIB Stop() {g_started = 0; return 0;}
bool __stdcall XPRESSNET_LIB Started() {return g_started;}
int __stdcall XPRESSNET_LIB OpenDevice(char *device, bool persist) {return 0;}
int __stdcall XPRESSNET_LIB GetDeviceCount() {return 1;}

// version
int __stdcall XPRESSNET_LIB GetDeviceVersion(char *version, unsigned int versionLen)
{
  wcscpy(version, L"--");
  return 0;
}
void __stdcall XPRESSNET_LIB GetDriverVersion(char *version, unsigned int versionLen)
{
  wcscpy(version, L"v 0.1");
  return;
}


bool __stdcall XPRESSNET_LIB IsModule(unsigned int module)
{
  if (module < 5) {
    return 1;
   } else {
    return 0;      
  }
}

unsigned int __stdcall XPRESSNET_LIB GetModuleCount(void) {
  return 4;
}

int __stdcall XPRESSNET_LIB GetModuleName(unsigned int module, char *name, unsigned int nameLen)
{
  //
  
  wcscpy(name, L"modul");
  
  if (module >= 5) {
    name[0] = 0;
    name[1] = 0; 
  }
  //strcpy(name, "mod");
  return 0;
}

int __stdcall XPRESSNET_LIB GetModuleFW(unsigned int module, char *fw, unsigned int fwLen)
{
  //
  wcscpy(fw, L"00");
  return 0;
}

// ToDo:
unsigned int __stdcall XPRESSNET_LIB GetLogLevel(void) {return 4;}
int __stdcall XPRESSNET_LIB Open() {g_opened = 1; return 0;}
int __stdcall XPRESSNET_LIB Close() {g_opened = 0; return 0;}
bool __stdcall XPRESSNET_LIB Opened() {return g_opened==1;}
int __stdcall XPRESSNET_LIB GetInput(unsigned int module, unsigned int port) {return 4;}
int __stdcall XPRESSNET_LIB GetOutput(unsigned int module, unsigned int port) {return 4;}
int __stdcall XPRESSNET_LIB SetOutput(unsigned int module, unsigned int port, int state) {return 4;} 

void __stdcall XPRESSNET_LIB GetDeviceSerial(int index, char *serial, unsigned int serialLen) {return;}

bool __stdcall XPRESSNET_LIB IsModuleFailure(unsigned int module) {return 0;}

int __stdcall XPRESSNET_LIB GetModuleType(unsigned int module)
{
  return 0x40; // UNI
}



void __stdcall XPRESSNET_LIB BindBeforeOpen(TStdNotifyEvent *event, void *Pointer){ return; }
void __stdcall XPRESSNET_LIB BindAfterOpen(TStdNotifyEvent *event, void *Pointer){ return; }
void __stdcall XPRESSNET_LIB BindBeforeClose(TStdNotifyEvent *event, void *Pointer){ return; }
void __stdcall XPRESSNET_LIB BindAfterClose(TStdNotifyEvent *event, void *Pointer){ return; }
void __stdcall XPRESSNET_LIB BindBeforeStart(TStdNotifyEvent *event, void *Pointer){ return; }
void __stdcall XPRESSNET_LIB BindAfterStart(TStdNotifyEvent *event, void *Pointer){ return; }
void __stdcall XPRESSNET_LIB BindBeforeStop(TStdNotifyEvent *event, void *Pointer){ return; }
void __stdcall XPRESSNET_LIB BindAfterStop(TStdNotifyEvent *event, void *Pointer){ return; }
void __stdcall XPRESSNET_LIB BindOnError(TStdErrorEvent event, void *Pointer){ return; }
void __stdcall XPRESSNET_LIB BindOnLog(TStdLogEvent *event, void *Pointer){ return; }
void __stdcall XPRESSNET_LIB BindOnInputChanged(TStdModuleChangeEvent *event, void *Pointer){ return; }
void __stdcall XPRESSNET_LIB BindOnOutputChanged(TStdModuleChangeEvent *event, void *Pointer){ return; }
void __stdcall XPRESSNET_LIB BindOnScanned(TStdNotifyEvent *event, void *Pointer){ return; }
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
