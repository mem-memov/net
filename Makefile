.DEFAULT_GOAL := net

net: main.o Gap.o Incoming.o Link.o Net.o Node.o Outgoing.o Space.o
	gcc main.o Gap.o Incoming.o Link.o Net.o Node.o Outgoing.o Space.o -o net

main.o: main.c
	gcc -c main.c

Gap.o: Gap.c Gap.h
	gcc -c Gap.c

Incoming.o: Incoming.c Incoming.h
	gcc -c Incoming.c

Link.o: Link.c Link.h Incoming.h Outgoing.h
	gcc -c Link.c

Net.o: Net.c Net.h Gap.h
	gcc -c Net.c

Node.o: Node.c Node.h Link.h
	gcc -c Node.c

Outgoing.o: Outgoing.c Outgoing.h
	gcc -c Outgoing.c

Space.o: Space.c Space.h Gap.h Link.h Net.h Node.h 
	gcc -c Space.c
	
clean:
	rm --force *.o net