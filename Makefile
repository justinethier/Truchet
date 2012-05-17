all: util.o truchet.o rects arcs filled-arcs four-arcs layered-arcs

lib: truchet.c truchet.h
	gcc -c truchet.c -o truchet.o
util: util.c util.h global-params.h
	gcc -c util.c -o util.o
four-arcs: util.o truchet.o four-arcs.c
	gcc -c four-arcs.c -o four-arcs.o
	gcc four-arcs.o truchet.o util.o -o four-arcs -lcxcore -lcv -lhighgui
arcs: util.o truchet.o arcs.c
	gcc -c arcs.c -o arcs.o
	gcc arcs.o truchet.o util.o -o arcs -lcxcore -lcv -lhighgui
filled-arcs: util.o truchet.o filled-arcs.c
	gcc -c filled-arcs.c -o filled-arcs.o
	gcc filled-arcs.o truchet.o util.o -o filled-arcs -lcxcore -lcv -lhighgui
layered-arcs: util.o truchet.o layered-arcs.c
	gcc -c layered-arcs.c -o layered-arcs.o
	gcc layered-arcs.o truchet.o util.o -o layered-arcs -lcxcore -lcv -lhighgui
rects: util.o truchet.o rects.c
	gcc -c rects.c -o rects.o
	gcc rects.o truchet.o util.o -o rects -lcxcore -lcv -lhighgui
clean:
	rm -f rects arcs four-arcs filled-arcs layered-arcs main *.o *.so out.png
