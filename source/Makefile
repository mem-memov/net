net: main.o Count.o CountError.o Counts.o Error.o Errors.o Export.o Exports.o Import.o Imports.o Gap.o Gaps.o Direction.o DirectionError.o Directions.o Link.o LinkError.o Links.o Mesh.o Meshes.o Net.o Nets.o Node.o NodeError.o Nodes.o Place.o Places.o Space.o Star.o Stars.o Stream.o Streams.o
	gcc main.o Count.o CountError.o Counts.o Error.o Errors.o Export.o Exports.o Import.o Imports.o Gap.o Gaps.o Direction.o DirectionError.o Directions.o Link.o LinkError.o Links.o Mesh.o Meshes.o Net.o Nets.o Node.o NodeError.o Nodes.o Place.o Places.o Space.o Star.o Stars.o Stream.o Streams.o -o net

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

Export.o: Export.c Export.h
	gcc -c Export.c

Exports.o: Exports.c Exports.h
	gcc -c Exports.c

Import.o: Import.c Import.h
	gcc -c Import.c

Imports.o: Imports.c Imports.h
	gcc -c Imports.c

Gap.o: Gap.c Gap.h
	gcc -c Gap.c

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

Mesh.o: Mesh.c Mesh.h
	gcc -c Mesh.c

Meshes.o: Meshes.c Meshes.h
	gcc -c Meshes.c

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

Star.o: Star.c Star.h
	gcc -c Star.c

Stars.o: Stars.c Stars.h
	gcc -c Stars.c
	
Stream.o: Stream.c Stream.h
	gcc -c Stream.c
	
Streams.o: Streams.c Streams.h
	gcc -c Streams.c
	
clean:
	rm --force *.o net