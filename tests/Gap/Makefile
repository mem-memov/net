all: build run clean

build: main.o
	gcc main.o -o test

main.o: main.c ../../source/Gap.c GapError.c
	gcc -c main.c

run: 
	./test
	
clean:
	rm --force *.o test
