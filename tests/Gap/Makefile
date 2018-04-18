.DEFAULT_GOAL := test

test: main.o
	gcc main.o -o test

main.o: main.c ../../source/Gap.c GapError.c
	gcc -c main.c
	
clean:
	rm --force *.o test
