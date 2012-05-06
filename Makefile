all: util lib rects arcs filled-arcs
lib: truchet.c truchet.h
	gcc -c truchet.c -o truchet.o
util: util.c util.h global-params.h
	gcc -c util.c -o util.o
arcs: util lib arcs.c
	gcc -c arcs.c -o arcs.o
	gcc arcs.o truchet.o util.o -o arcs -lcxcore -lcv -lhighgui
filled-arcs: util lib filled-arcs.c
	gcc -c filled-arcs.c -o filled-arcs.o
	gcc filled-arcs.o truchet.o util.o -o filled-arcs -lcxcore -lcv -lhighgui
rects: util lib rects.c
	gcc -c rects.c -o rects.o
	gcc rects.o truchet.o util.o -o rects -lcxcore -lcv -lhighgui
clean:
	rm -f rects arcs filled-arcs main *.o *.so
