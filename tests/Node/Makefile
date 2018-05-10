all: build run clean

build: main.o
	gcc main.o -o test

main.o: main.c ../../source/Node.c Count.c Link.c NodeError.c Place.c
	gcc -c main.c

run: 
	./test
	
clean:
	rm --force *.o test
