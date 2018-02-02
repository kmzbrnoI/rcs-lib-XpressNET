////////////////////////////////////////////////////////////////////////////////
//  LibraryEvents.pas
//  MTB simulator library.
//  Definition of library events.
//  (c) Jan Horacek (jan.horacek@kmz-brno.cz),
//      Michal Petrilak (engineercz@gmail.com)
////////////////////////////////////////////////////////////////////////////////

/*
   LICENSE:
   Copyright 2015-2017 Michal Petrilak, Jan Horacek
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
       http://www.apache.org/licenses/LICENSE-2.0
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
#ifndef LIBRARYEVENTS_H
#define LIBRARYEVENTS_H

typedef void (__stdcall *TStdNotifyEvent)(void *Sender, void *data);
typedef void (__stdcall *TStdLogEvent)(void *Sender, void *data, char *msg);
typedef void (__stdcall *TStdErrorEvent)(void *Sender, void *data, unsigned short int errValue, unsigned char errAddr, char *errMsg);
typedef void (__stdcall *TStdModuleChangeEvent)(void *Sender, void *data, unsigned char module);

struct TMyErrorEvent {
	TStdNotifyEvent event;
	void *data;
};

struct TMyNotifyEvent {
	TStdNotifyEvent event;
	void *data;
};

struct TMyModuleChangeEvent {
	TStdModuleChangeEvent event;
	void *data;
};

struct TLibEvents {
	struct TMyNotifyEvent BeforeOpen;
	struct TMyNotifyEvent AfterOpen;
	struct TMyNotifyEvent BeforeClose;
	struct TMyNotifyEvent AfterClose;

  struct TMyNotifyEvent BeforeStart;
	struct TMyNotifyEvent AfterStart;
  struct TMyNotifyEvent BeforeStop;
	struct TMyNotifyEvent AfterStop;

  struct TMyErrorEvent         OnError;
  struct TMyModuleChangeEvent  OnInputChanged;
  struct TMyModuleChangeEvent  OnOutputChanged;
  struct TMyNotifyEvent        OnScanned;
  struct TMyNotifyEvent        OnLog;
};

extern struct TLibEvents LibEvents;

#endif