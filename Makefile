all: util lib main
lib: truchet.c truchet.h
	gcc -c truchet.c -o truchet.o
util: util.c util.h
	gcc -c util.c -o util.o
main: util lib main.c
	gcc -c main.c -o main.o
	gcc main.o truchet.o util.o -o main -lcxcore -lcv -lhighgui
clean:
	rm -f main *.o *.so
