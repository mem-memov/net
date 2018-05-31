netgraph: main.o Count.o CountError.o Counts.o Direction.o DirectionError.o Directions.o Error.o Errors.o Export.o Exports.o Gap.o Gaps.o Graph.o Import.o Imports.o Link.o LinkError.o Links.o Mesh.o Meshes.o Net.o NetError.o Nets.o Node.o NodeError.o Nodes.o Place.o Places.o Star.o StarError.o Stars.o Stream.o Streams.o Telescope.o Telescopes.o
	gcc  main.o Count.o CountError.o Counts.o Direction.o DirectionError.o Directions.o Error.o Errors.o Export.o Exports.o Gap.o Gaps.o Graph.o Import.o Imports.o Link.o LinkError.o Links.o Mesh.o Meshes.o Net.o Nets.o NetError.o Node.o NodeError.o Nodes.o Place.o Places.o Star.o StarError.o Stars.o Stream.o Streams.o Telescope.o Telescopes.o -o netgraph

main.o: main.c
	gcc -Wall -c main.c

Count.o: Count.c Count.h
	gcc -Wall -c Count.c

CountError.o: CountError.c CountError.h
	gcc -Wall -c CountError.c

Counts.o: Counts.c Counts.h
	gcc -Wall -c Counts.c

Direction.o: Direction.c Direction.h
	gcc -Wall -c Direction.c

DirectionError.o: Direction.c DirectionError.h
	gcc -Wall -c DirectionError.c

Directions.o: Directions.c Directions.h
	gcc -Wall -c Directions.c

Error.o: Error.c Error.h
	gcc -Wall -c Error.c

Errors.o: Errors.c Errors.h
	gcc -Wall -c Errors.c

Export.o: Export.c Export.h
	gcc -Wall -c Export.c

Exports.o: Exports.c Exports.h
	gcc -Wall -c Exports.c

Gap.o: Gap.c Gap.h
	gcc -Wall -c Gap.c

Gaps.o: Gaps.c Gaps.h
	gcc -Wall -c Gaps.c

Graph.o: Graph.c Graph.h Links.h Nets.h Nodes.h Places.h
	gcc -Wall -c Graph.c

Import.o: Import.c Import.h
	gcc -Wall -c Import.c

Imports.o: Imports.c Imports.h
	gcc -Wall -c Imports.c

Link.o: Link.c Link.h
	gcc -Wall -c Link.c
	
LinkError.o: LinkError.c LinkError.h
	gcc -Wall -c LinkError.c
	
Links.o: Links.c Links.h
	gcc -Wall -c Links.c

Mesh.o: Mesh.c Mesh.h
	gcc -Wall -c Mesh.c

Meshes.o: Meshes.c Meshes.h
	gcc -Wall -c Meshes.c

Net.o: Net.c Net.h
	gcc -Wall -c Net.c

NetError.o: NetError.c NetError.h
	gcc -Wall -c NetError.c

Nets.o: Nets.c Nets.h
	gcc -Wall -c Nets.c

Node.o: Node.c Node.h
	gcc -Wall -c Node.c

NodeError.o: NodeError.c NodeError.h
	gcc -Wall -c NodeError.c
	
Nodes.o: Nodes.c Nodes.h
	gcc -Wall -c Nodes.c
	
Place.o: Place.c Place.h
	gcc -Wall -c Place.c
	
Places.o: Places.c Places.h
	gcc -Wall -c Places.c

Star.o: Star.c Star.h
	gcc -Wall -c Star.c

StarError.o: StarError.c StarError.h
	gcc -Wall -c StarError.c

Stars.o: Stars.c Stars.h
	gcc -Wall -c Stars.c
	
Stream.o: Stream.c Stream.h
	gcc -Wall -c Stream.c
	
Streams.o: Streams.c Streams.h
	gcc -Wall -c Streams.c
	
Telescope.o: Telescope.c Telescope.h
	gcc -Wall -c Telescope.c
	
Telescopes.o: Telescopes.c Telescopes.h
	gcc -Wall -c Telescopes.c
	
clean:
	rm --force *.o netgraph libnetgraph.a

install:
	install netgraph /usr/local/bin/netgraph && rm --force main.o && ar -rcs libnetgraph.a *.o && cp libnetgraph.a /usr/local/lib/libnetgraph.a && cp Graph.h /usr/local/include/netgraph.h

uninstall:
	rm --force netgraph /usr/local/bin/netgraph /usr/local/lib/libnetgraph.a /usr/local/include/netgraph.h