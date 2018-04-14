.DEFAULT_GOAL := net

net: main.o Gap.o Direction.o Link.o Net.o Node.o Space.o
	gcc main.o Gap.o Direction.o Link.o Net.o Node.o Space.o -o net

main.o: main.c
	gcc -c main.c

Gap.o: Gap.c Gap.h
	gcc -c Gap.c

Direction.o: Direction.c Direction.h
	gcc -c Direction.c

Link.o: Link.c Link.h Direction.h
	gcc -c Link.c

Net.o: Net.c Net.h Gap.h
	gcc -c Net.c

Node.o: Node.c Node.h Link.h
	gcc -c Node.c

Space.o: Space.c Space.h Link.h Net.h Node.h 
	gcc -c Space.c
	
clean:
	rm --force *.o net