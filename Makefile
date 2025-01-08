all: main

main: main.c dict.c main.h dict.h
	gcc -g -o main main.c dict.c

clean:
	rm -f main
