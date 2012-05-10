main: main.c
	gcc main.c -o main -lcxcore -lcv -lhighgui
clean:
	rm -f main
