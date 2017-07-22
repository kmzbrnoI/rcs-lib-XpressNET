all:	XpressNET_acc.dll

XpressNET_acc.o:
	gcc -c -pipe -fPIC -fno-keep-inline-dllexport -O2 -w -DUNICODE -DXPRESSNET_ACC_LIBRARY -I. -IF:/Qt/5.8/mingw53_32/include  -o XpressNET_acc.o XpressNET_acc.c

XpressNET_acc.dll: XpressNET_acc.o
	gcc   -shared -Wl,--enable-stdcall-fixup -Wl,-s --enable-stdcall-fixup -o XpressNET_acc.dll XpressNET_acc.o XpressNET_acc.def

clean:
	rm XpressNET_acc.o xpressNET_acc.dll > /dev/null

install:	all
	cp XpressNET_acc.dll D:/Michal/prog/Delphi2009/hJOP/server/rcs/

# @rem -Wall -Wextra