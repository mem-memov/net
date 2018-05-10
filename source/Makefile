net: main.o Count.o CountError.o Counts.o Error.o Errors.o Gap.o GapError.o Gaps.o Direction.o DirectionError.o Directions.o Link.o LinkError.o Links.o Net.o Nets.o Node.o NodeError.o Nodes.o Place.o Places.o Space.o
	gcc main.o Count.o CountError.o Counts.o Error.o Errors.o Gap.o GapError.o Gaps.o Direction.o DirectionError.o Directions.o Link.o LinkError.o Links.o Net.o Nets.o Node.o NodeError.o Nodes.o Place.o Places.o Space.o -o net

main.o: main.c
	gcc -c main.c

Count.o: Count.c Count.h
	gcc -c Count.c

CountError.o: CountError.c CountError.h
	gcc -c CountError.c

Counts.o: Counts.c Counts.h
	gcc -c Counts.c

Error.o: Error.c Error.h
	gcc -c Error.c

Errors.o: Errors.c Errors.h
	gcc -c Errors.c

Gap.o: Gap.c Gap.h
	gcc -c Gap.c

GapError.o: GapError.c GapError.h
	gcc -c GapError.c

Gaps.o: Gaps.c Gaps.h
	gcc -c Gaps.c

Direction.o: Direction.c Direction.h
	gcc -c Direction.c

DirectionError.o: Direction.c DirectionError.h
	gcc -c DirectionError.c

Directions.o: Directions.c Directions.h
	gcc -c Directions.c

Link.o: Link.c Link.h
	gcc -c Link.c
	
LinkError.o: LinkError.c LinkError.h
	gcc -c LinkError.c
	
Links.o: Links.c Links.h
	gcc -c Links.c

Net.o: Net.c Net.h
	gcc -c Net.c

Nets.o: Nets.c Nets.h
	gcc -c Nets.c

Node.o: Node.c Node.h
	gcc -c Node.c

NodeError.o: NodeError.c NodeError.h
	gcc -c NodeError.c
	
Nodes.o: Nodes.c Nodes.h
	gcc -c Nodes.c
	
Place.o: Place.c Place.h
	gcc -c Place.c
	
Places.o: Places.c Places.h
	gcc -c Places.c

Space.o: Space.c Space.h Links.h Nets.h Nodes.h Places.h
	gcc -c Space.c
	
clean:
	rm --force *.o net