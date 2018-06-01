#include "Graph.h"
#include <stdlib.h>
#include <stdio.h>
#include "Counts.h"
#include "Errors.h"
#include "Exports.h"
#include "Imports.h"
#include "Knitters.h"
#include "Links.h"
#include "Boats.h"
#include "Nodes.h"
#include "Places.h"
#include "Spaces.h"
#include "Stars.h"
#include "Streams.h"
#include "Telescopes.h"

struct Graph {
	size_t graphSize;
	size_t entrySize;
	size_t placeSize;
	unsigned char * bytes;
	struct Boat * boat;

	// factories
	struct Streams * streams;
	struct Counts * counts;
	struct Errors * errors;
	struct Links * links;
	struct Boats * boats;
	struct Nodes * nodes;
	struct Places * places;
	struct Stars * stars;
	struct Imports * imports;
	
	// pool
	struct Node * node;
	struct Node * originNode;
	struct Node * destinationNode;
	struct Link * link;
};

struct Graph * Graph_construct(size_t graphSize)
{
	struct Graph * this = malloc(sizeof(struct Graph));
	
	if (graphSize < 1) {
		exit(0);
	}
	
	this->graphSize = graphSize;
	this->entrySize = 6;
	this->placeSize = 4;
	this->bytes = malloc(this->graphSize * this->entrySize * this->placeSize);
	
	// factories
	this->errors = Errors_construct(Error_construct());
	this->places = Places_construct(this->placeSize, this->bytes);
	
	this->streams = Streams_construct(this->bytes);
	
	this->counts = Counts_construct(
		this->places, 
		Errors_makeCountError(this->errors)
	);
	
	this->boats = Boats_construct(
		this->places, 
		this->counts, 
		Knitters_construct(
			Meshes_construct(
				Gaps_construct(this->places)
			),
			this->places,
			Spaces_construct(graphSize),
			Errors_makeKnitterError(this->errors)
		),
		Exports_construct(this->streams),
		Errors_makeBoatError(this->errors)
	);
	
	this->links = Links_construct(
		Errors_makeLinkError(this->errors), 
		Directions_construct(
			this->places, 
			Errors_makeDirectionError(this->errors)
		)
	);

	this->stars = Stars_construct(
		this->links,
		Telescopes_construct(
			this->links
		),
		Errors_makeStarError(this->errors)
	);
	
	this->nodes = Nodes_construct(
		this->places, 
		this->counts, 
		this->stars, 
		Errors_makeNodeError(this->errors)
	);
	
	this->boat = Boats_make(this->boats, this->graphSize, this->entrySize);
	
	this->imports = Imports_construct(this->streams, this->entrySize, this->placeSize, this->boat);

	// pool
	this->node = Nodes_make(this->nodes);
	this->originNode = Nodes_make(this->nodes);
	this->destinationNode = Nodes_make(this->nodes);
	this->link = Links_make(this->links);
	
	Boat_create(this->boat, this->placeSize);

	return this;
}

void Graph_destruct(struct Graph * this)
{
	free(this->places);
	this->places = NULL;
	
	// fields
	Boat_destruct(this->boat);
	
	// pool
	Node_destruct(this->node);
	Node_destruct(this->originNode);
	Node_destruct(this->destinationNode);
	Link_destruct(this->link);
	
	// factories
	Counts_destruct(this->counts);
	Boats_destruct(this->boats);
	Stars_destruct(this->stars);
	Links_destruct(this->links);
	Nodes_destruct(this->nodes);
	Places_destruct(this->places);
	Errors_destruct(this->errors);
	
	Imports_destruct(this->imports);
	Streams_destruct(this->streams);
	
	free(this);
	this = NULL;
}

char Graph_hasFreePlace(struct Graph * this)
{
	return Boat_hasSpaceForEntry(this->boat);
}

size_t Graph_addNode(struct Graph * this)
{
	size_t place = Boat_createNodeEntry(this->boat);
	
	Node_create(this->node, place);

	return place;
}

void Graph_removeNode(struct Graph * this, size_t place)
{
	size_t * nodes;
	size_t length;
	size_t i;
	
	Graph_getNodeDestinations(this, place, &nodes, &length);
	for (i = 0; i < length; i++) {
		Graph_disconnectNodes(this, place, nodes[i]);
	}
	free(nodes);
	nodes = NULL;
	
	Graph_getNodeOrigins(this, place, &nodes, &length);
	for (i = 0; i < length; i++) {
		Graph_disconnectNodes(this, nodes[i], place);
	}
	free(nodes);
	nodes = NULL;
	
	Node_read(this->node, place);
	Node_delete(this->node);
	
	Boat_deleteNodeEntry(this->boat, place);
}

void Graph_connectNodes(struct Graph * this, size_t origin, size_t destination)
{
	Node_read(this->originNode, origin);
	Node_read(this->destinationNode, destination);

	size_t link = Boat_createLinkEntry(this->boat);
	Link_create(this->link, link, origin, destination);

	Node_addOutgoingLink(this->originNode, this->link);
	Node_addIncomingLink(this->destinationNode, this->link);
}

void Graph_disconnectNodes(struct Graph * this, size_t origin, size_t destination)
{
	size_t deletedOutgoingLink;
	size_t deletedIncomingLink;
	
	Node_read(this->originNode, origin);
	Node_read(this->destinationNode, destination);
	
	if ( Node_isSmallOrigin(this->originNode, this->destinationNode) ) {

		deletedOutgoingLink = Node_deleteDestination(this->originNode, destination);

		if ( 0 == deletedOutgoingLink ) {
			return;
		}

		Node_deleteIncomingLink(this->destinationNode);

		Boat_deleteLinkEntry(this->boat, deletedOutgoingLink);

	} else {

		deletedIncomingLink = Node_deleteOrigin(this->destinationNode, origin);

		if ( 0 == deletedIncomingLink ) {
			return;
		}

		Node_deleteOutgoingLink(this->originNode);

		Boat_deleteLinkEntry(this->boat, deletedIncomingLink);

	}
}

void Graph_getNodeDestinations(struct Graph * this, size_t origin, size_t ** destinations, size_t * length)
{
	Node_read(this->node, origin);
	
	Node_getNodeDestinations(this->node, destinations, length);
}

void Graph_getNodeOrigins(struct Graph * this, size_t destination, size_t ** origins, size_t * length)
{
	Node_read(this->node, destination);
	
	Node_getNodeOrigins(this->node, origins, length);
}

char Graph_isNode(struct Graph * this, size_t place)
{
	if ( ! Boat_isCovering(this->boat, place)) {
		return 0;
	}
	
	Node_read(this->node, place);

	return Node_isNode(this->node);
}

void Graph_export(struct Graph * this, FILE * file)
{
	struct Export * export = Boat_createExport(this->boat);
	
	Export_write(export, file);
	
	Export_destruct(export);
}

void Graph_import(struct Graph * this, FILE * file)
{
	struct Import * import = Imports_make(this->imports);
	
	Import_read(import, file);
	
	Import_destruct(import);
}
