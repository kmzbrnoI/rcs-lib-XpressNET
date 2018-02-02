#ifndef XPRESSNET_LIB_H
#define XPRESSNET_LIB_H

#include <windows.h> 

#ifdef BUILDING_XPRESSNET_LIB
//#define XPRESSNET_LIB __declspec(dllexport)
#define XPRESSNET_LIB
#else
#define XPRESSNET_LIB __declspec(dllimport)
#endif

typedef int bool; // C do not know bool

//function LoadConfig(filename:PChar):Integer 
int __stdcall XPRESSNET_LIB LoadConfig(char* filename);
//function SaveConfig(filename:PChar):Integer
int __stdcall XPRESSNET_LIB SaveConfig(char* filename);
//procedure SetLogLevel(loglevel:Cardinal)
void __stdcall XPRESSNET_LIB SetLogLevel(unsigned int loglevel);
//function GetLogLevel():Cardinal
unsigned int __stdcall XPRESSNET_LIB GetLogLevel(void);
// procedure ShowConfigDialog()
void __stdcall XPRESSNET_LIB ShowConfigDialog();
// procedure HideConfigDialog()
void __stdcall XPRESSNET_LIB HideConfigDialog();
// function Open():Integer
int __stdcall XPRESSNET_LIB Open();
// function OpenDevice(device:PChar; persist:boolean):Integer
int __stdcall XPRESSNET_LIB OpenDevice(char *device, bool persist);
// function Close():Integer
int __stdcall XPRESSNET_LIB Close();
// function Opened():Boolean
bool __stdcall XPRESSNET_LIB Opened();
// function Start():Integer
int __stdcall XPRESSNET_LIB Start();
// function Stop():Integer
int __stdcall XPRESSNET_LIB Stop();
// function Started():Boolean
bool __stdcall XPRESSNET_LIB Started();
// function GetInput(module, unsigned int portl):Integer
int __stdcall XPRESSNET_LIB GetInput(unsigned int module, unsigned int port);
// function GetOutput(module, unsigned int portl):Integer 
int __stdcall XPRESSNET_LIB GetOutput(unsigned int module, unsigned int port); 
// function SetOutput(module, unsigned int portl; state:Integer):Integer 
int __stdcall XPRESSNET_LIB SetOutput(unsigned int module, unsigned int port, int state); 
// function GetDeviceCount():Integer 
int __stdcall XPRESSNET_LIB GetDeviceCount();
// procedure GetDeviceSerial(index:Integer, serial:PChar, serialLen:Cardinal) 
void __stdcall XPRESSNET_LIB GetDeviceSerial(int index, char *serial, unsigned int serialLen);
// function IsModule(module:Cardinal):Boolean 
bool __stdcall XPRESSNET_LIB IsModule(unsigned int module);
// function IsModuleFailure(module:Cardinal):Boolean 
bool __stdcall XPRESSNET_LIB IsModuleFailure(unsigned int module);
// function GetModuleCount():Cardinal 
unsigned int __stdcall XPRESSNET_LIB GetModuleCount(void);
// function GetModuleType(module:Cardinal):Integer 
int __stdcall XPRESSNET_LIB GetModuleType(unsigned int module);
// function GetModuleName(module:Cardinal; name:PChar; nameLen:Cardinal):Integer 
int __stdcall XPRESSNET_LIB GetModuleName(unsigned int module, char *name, unsigned int nameLen);
// function GetModuleFW(module:Cardinal; fw:PChar; fwLen:Cardinal):Integer 
int __stdcall XPRESSNET_LIB GetModuleFW(unsigned int module, char *fw, unsigned int fwLen);
// function GetDeviceVersion(version:PChar; versionLen:Cardinal):Integer 
int __stdcall XPRESSNET_LIB GetDeviceVersion(char *version, unsigned int versionLen);
// procedure GetDriverVersion(version:PChar; versionLen:Cardinal) 
void __stdcall XPRESSNET_LIB GetDriverVersion(char *version, unsigned int versionLen);

/*
procedure BindBeforeOpen(event:TStdNotifyEvent; data:Pointer)
procedure BindAfterOpen(event:TStdNotifyEvent; data:Pointer)
procedure BindBeforeClose(event:TStdNotifyEvent; data:Pointer)
procedure BindAfterClose(event:TStdNotifyEvent; data:Pointer)
procedure BindBeforeStart(event:TStdNotifyEvent; data:Pointer)
procedure BindAfterStart(event:TStdNotifyEvent; data:Pointer)
procedure BindBeforeStop(event:TStdNotifyEvent; data:Pointer)
procedure BindAfterStop(event:TStdNotifyEvent; data:Pointer)
procedure BindOnError(event:TStdErrorEvent; data:Pointer)
procedure BindOnLog(event:TStdLogEvent; data:Pointer)
procedure BindOnInputChanged(event:TStdModuleChangeEvent; data:Pointer)
procedure BindOnOutputChanged(event:TStdModuleChangeEvent; data:Pointer)
procedure BindOnScanned(event:TStdNotifyEvent; data:Pointer)
*/

/*
TStdNotifyEvent = procedure (Sender: TObject; data:Pointer); stdcall;
TStdLogEvent = procedure (Sender: TObject; data:Pointer; logLevel:Integer; msg:PChar); stdcall;
TStdErrorEvent = procedure (Sender: TObject; data:Pointer; errValue: word; errAddr: byte; errMsg:PChar); stdcall;
TStdModuleChangeEvent = procedure (Sender: TObject; data:Pointer; module: byte); stdcall;
*/

void __stdcall XPRESSNET_LIB BindBeforeOpen(TStdNotifyEvent *event, void *data);
void __stdcall XPRESSNET_LIB BindAfterOpen(TStdNotifyEvent *event, void *data);
void __stdcall XPRESSNET_LIB BindBeforeClose(TStdNotifyEvent *event, void *data);
void __stdcall XPRESSNET_LIB BindAfterClose(TStdNotifyEvent *event, void *data);
void __stdcall XPRESSNET_LIB BindBeforeStart(TStdNotifyEvent *event, void *data);
void __stdcall XPRESSNET_LIB BindAfterStart(TStdNotifyEvent *event, void *data);
void __stdcall XPRESSNET_LIB BindBeforeStop(TStdNotifyEvent *event, void *data);
void __stdcall XPRESSNET_LIB BindAfterStop(TStdNotifyEvent *event, void *data);
void __stdcall XPRESSNET_LIB BindOnError(TStdErrorEvent event, void *data);
void __stdcall XPRESSNET_LIB BindOnLog(TStdLogEvent *event, void *data);
void __stdcall XPRESSNET_LIB BindOnInputChanged(TStdModuleChangeEvent *event, void *data);
void __stdcall XPRESSNET_LIB BindOnOutputChanged(TStdModuleChangeEvent *event, void *data);
void __stdcall XPRESSNET_LIB BindOnScanned(TStdNotifyEvent *event, void *data);

HINSTANCE win_hinst;


#endif  // XPRESSNET_LIB_H
