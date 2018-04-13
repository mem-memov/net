.DEFAULT_GOAL := net

net: main.o Gap.o Link.o Net.o Node.o Space.o
	gcc main.o Gap.o Link.o Net.o Node.o Space.o -o net

main.o: main.c
	gcc -c main.c

Gap.o: Gap.c Gap.h
	gcc -c Gap.c

Link.o: Link.c Link.h
	gcc -c Link.c

Net.o: Net.c Net.h Gap.h
	gcc -c Net.c

Node.o: Node.c Node.h Link.h
	gcc -c Node.c

Space.o: Space.c Space.h Gap.h Link.h Net.h Node.h 
	gcc -c Space.c
	
clean:
	rm --force *.o net