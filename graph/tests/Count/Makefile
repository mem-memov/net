all: build run clean

build: main.o
	gcc main.o -o test

main.o: main.c ../../source/Count.c ../CountError.c ../Place.c
	gcc -c main.c

run: 
	./test
	
clean:
	rm --force *.o test
