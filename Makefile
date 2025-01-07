all: main

main: main.c dict.c main.h dict.h
	gcc -o main main.c dict.c

clean:
	rm -f main
