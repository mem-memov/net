net: main.o Gap.o GapError.o Direction.o DirectionError.o Link.o Net.o Node.o NodeError.o Space.o
	gcc main.o Gap.o GapError.o Direction.o DirectionError.o Link.o Net.o Node.o NodeError.o Space.o -o net

main.o: main.c
	gcc -c main.c

Gap.o: Gap.c Gap.h GapError.h
	gcc -c Gap.c

GapError.o: GapError.c GapError.h
	gcc -c GapError.c

Direction.o: Direction.c Direction.h DirectionError.h
	gcc -c Direction.c

DirectionError.o: Direction.c DirectionError.h
	gcc -c DirectionError.c

Link.o: Link.c Link.h Direction.h DirectionError.h
	gcc -c Link.c

Net.o: Net.c Net.h Gap.h GapError.h
	gcc -c Net.c

Node.o: Node.c Node.h Link.h
	gcc -c Node.c

NodeError.o: NodeError.c NodeError.h
	gcc -c NodeError.c

Space.o: Space.c Space.h Link.h Net.h Node.h 
	gcc -c Space.c
	
clean:
	rm --force *.o net