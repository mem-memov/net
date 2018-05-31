all: build run clean

build: main.o
	gcc main.o -o test

main.o: main.c ../../source/Net.c ../Count.c ../Export.c ../Exports.c ../Mesh.c ../NetError.c ../Place.c ../Stream.c
	gcc -c main.c

run: 
	./test
	
clean:
	rm --force *.o test
