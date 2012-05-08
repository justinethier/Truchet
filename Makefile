all: util lib rects arcs filled-arcs four-arcs layered-arcs

lib: truchet.c truchet.h
	gcc -c truchet.c -o truchet.o
util: util.c util.h global-params.h
	gcc -c util.c -o util.o
four-arcs: util lib four-arcs.c
	gcc -c four-arcs.c -o four-arcs.o
	gcc four-arcs.o truchet.o util.o -o four-arcs -lcxcore -lcv -lhighgui
arcs: util lib arcs.c
	gcc -c arcs.c -o arcs.o
	gcc arcs.o truchet.o util.o -o arcs -lcxcore -lcv -lhighgui
filled-arcs: util lib filled-arcs.c
	gcc -c filled-arcs.c -o filled-arcs.o
	gcc filled-arcs.o truchet.o util.o -o filled-arcs -lcxcore -lcv -lhighgui
layered-arcs: util lib layered-arcs.c
	gcc -c layered-arcs.c -o layered-arcs.o
	gcc layered-arcs.o truchet.o util.o -o layered-arcs -lcxcore -lcv -lhighgui
rects: util lib rects.c
	gcc -c rects.c -o rects.o
	gcc rects.o truchet.o util.o -o rects -lcxcore -lcv -lhighgui
clean:
	rm -f rects arcs filled-arcs layered-arcs main *.o *.so out.png
