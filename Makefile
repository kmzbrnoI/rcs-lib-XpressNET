# Declaration of variables
#CC = c:\MinGW\mingw32\bin\gcc.exe 
CC = c:\MinGW\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin\gcc.exe
CC_FLAGS = -pipe -fPIC -fno-keep-inline-dllexport -O2 -w -DUNICODE -DXPRESSNET_ACC_LIBRARY -I.
#CC_FFLAGS = -shared -Wl,--enable-stdcall-fixup -Wl,-s
CC_FFLAGS = -shared -Wl,--enable-stdcall-fixup -municode

SHELL := /bin/bash
PATH := c:\MinGW\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin\;$(PATH)

# File names
EXEC = XpressNET_acc.dll
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
DEF     = $(EXEC:.dll=.def)

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(CC_FFLAGS) $(OBJECTS) $(DEF) -o $(EXEC)

# To obtain object files
%.o: %.c
	$(CC) -c $(CC_FLAGS) -o $@ $<

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)

# force rebuild
rebuild: clean all

all: $(EXEC)

install: $(EXEC)
	cp XpressNET_acc.dll D:/Michal/prog/Delphi2009/hJOP/server/rcs/

test:
	echo $$PATH
	echo
	echo $$SHELL
#  export PATH=bin:$$PATH;
# @rem -Wall -Wextra