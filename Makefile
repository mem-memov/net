.DEFAULT_GOAL := net

net: main.o Gap.o Space.o
	gcc main.o Gap.o Space.o -o net

main.o: main.c
	gcc -c main.c

Gap.o: Gap.c Gap.h
	gcc -c Gap.c

Space.o: Space.c Space.h Gap.h
	gcc -c Space.c
	
clean:
	rm --force *.o net