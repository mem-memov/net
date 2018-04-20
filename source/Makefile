CC=gcc
CFLAGS= -dNDEBUG

net: main.o Gap.o GapError.o Direction.o DirectionError.o Link.o Net.o Node.o Space.o
	$(CC) main.o Gap.o GapError.o Direction.o DirectionError.o Link.o Net.o Node.o Space.o -o net

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

Gap.o: Gap.c Gap.h GapError.h
	$(CC) $(CFLAGS) -c Gap.c

GapError.o: GapError.c GapError.h
	$(CC) $(CFLAGS) -c GapError.c

Direction.o: Direction.c Direction.h DirectionError.h
	$(CC) $(CFLAGS) -c Direction.c

DirectionError.o: Direction.c DirectionError.h
	$(CC) $(CFLAGS) -c DirectionError.c

Link.o: Link.c Link.h Direction.h DirectionError.h
	$(CC) $(CFLAGS) -c Link.c

Net.o: Net.c Net.h Gap.h GapError.h
	$(CC) $(CFLAGS) -c Net.c

Node.o: Node.c Node.h Link.h
	$(CC) $(CFLAGS) -c Node.c

Space.o: Space.c Space.h Link.h Net.h Node.h 
	$(CC) $(CFLAGS) -c Space.c
	
clean:
	rm --force *.o net