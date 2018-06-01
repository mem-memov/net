all: build run clean

build: main.o
	gcc main.o -o test

main.o: main.c ../../source/Boat.c ../Count.c ../Export.c ../Exports.c ../Mesh.c ../BoatError.c ../Place.c ../Stream.c
	gcc -c main.c

run: 
	./test
	
clean:
	rm --force *.o test
