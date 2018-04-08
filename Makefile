.DEFAULT_GOAL := net

net: main.o Error.o Link.o Net.o Node.o
	gcc main.o Error.o Link.o Net.o Node.o -o net

main.o: main.c
	gcc -c main.c

Error.o: Error.c Error.h
	gcc -c Error.c

Link.o: Link.c Link.h Node.h
	gcc -c Link.c

Net.o: Net.c Net.h Node.h
	gcc -c Net.c

Node.o: Node.c Node.h Link.h
	gcc -c Node.c
	
clean:
	rm --force *.o net