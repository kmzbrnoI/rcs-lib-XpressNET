# Declaration of variables
CC = c:\MinGW\mingw32\bin\gcc.exe 
CC_FLAGS = -pipe -fPIC -fno-keep-inline-dllexport -O2 -w -DUNICODE -DXPRESSNET_ACC_LIBRARY -I.
#CC_FFLAGS = -shared -Wl,--enable-stdcall-fixup -Wl,-s
CC_FFLAGS = -shared -Wl,--enable-stdcall-fixup -municode

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

# @rem -Wall -Wextra