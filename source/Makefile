net: main.o Entry.o Gap.o GapError.o Gaps.o Direction.o DirectionError.o Link.o LinkError.o Net.o Node.o NodeError.o Space.o
	gcc main.o Entry.o Gap.o GapError.o Gaps.o Direction.o DirectionError.o Link.o LinkError.o Net.o Node.o NodeError.o Space.o -o net

main.o: main.c
	gcc -c main.c

Entry.o: Entry.c Entry.h
	gcc -c Entry.c

Gap.o: Gap.c Gap.h GapError.h
	gcc -c Gap.c

GapError.o: GapError.c GapError.h
	gcc -c GapError.c

Gaps.o: Gaps.c Gaps.h
	gcc -c Gaps.c

Direction.o: Direction.c Direction.h DirectionError.h
	gcc -c Direction.c

DirectionError.o: Direction.c DirectionError.h
	gcc -c DirectionError.c

Link.o: Link.c Link.h Direction.h LinkError.h
	gcc -c Link.c
	
LinkError.o: LinkError.c LinkError.h
	gcc -c LinkError.c

Net.o: Net.c Net.h Entry.h Gap.h GapError.h
	gcc -c Net.c

Node.o: Node.c Node.h Link.h
	gcc -c Node.c

NodeError.o: NodeError.c NodeError.h
	gcc -c NodeError.c

Space.o: Space.c Space.h Link.h Net.h Node.h 
	gcc -c Space.c
	
clean:
	rm --force *.o net