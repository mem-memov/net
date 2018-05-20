#include "Graph.h"
#include <stdlib.h>
#include <stdio.h>
#include "Counts.h"
#include "Errors.h"
#include "Exports.h"
#include "Imports.h"
#include "Links.h"
#include "Nets.h"
#include "Nodes.h"
#include "Places.h"
#include "Stars.h"
#include "Streams.h"

struct Graph {
	size_t graphSize;
	size_t entrySize;
	size_t placeSize;
	unsigned char * bytes;
	struct Net * net;

	// factories
	struct Streams * streams;
	struct Counts * counts;
	struct Errors * errors;
	struct Links * links;
	struct Nets * nets;
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
	
	this->nets = Nets_construct(
		this->places, 
		this->counts, 
		Meshes_construct(
			Gaps_construct(this->places)
		),
		Exports_construct(this->streams)
	);
	
	this->links = Links_construct(
		Errors_makeLinkError(this->errors), 
		Directions_construct(
			this->places, 
			Errors_makeDirectionError(this->errors)
		)
	);
	
	this->stars = Stars_construct(this->links);
	
	this->nodes = Nodes_construct(
		this->places, 
		this->counts, 
		this->stars, 
		Errors_makeNodeError(this->errors)
	);
	
	this->net = Nets_make(this->nets, this->graphSize, this->entrySize);
	
	this->imports = Imports_construct(this->streams, this->entrySize, this->placeSize, this->net);

	// pool
	this->node = Nodes_make(this->nodes);
	this->originNode = Nodes_make(this->nodes);
	this->destinationNode = Nodes_make(this->nodes);
	this->link = Links_make(this->links);
	
	Net_create(this->net, this->placeSize);

	return this;
}

void Graph_destruct(struct Graph * this)
{
	free(this->places);
	this->places = NULL;
	
	// fields
	Net_destruct(this->net);
	
	// pool
	Node_destruct(this->node);
	Node_destruct(this->originNode);
	Node_destruct(this->destinationNode);
	Link_destruct(this->link);
	
	// factories
	Counts_destruct(this->counts);
	Nets_destruct(this->nets);
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
	return Net_hasGraphForEntry(this->net);
}

size_t Graph_addNode(struct Graph * this)
{
	size_t place = Net_createEntry(this->net, 1);
	
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
	
	Net_addGap(this->net, place, 1);
}

void Graph_connectNodes(struct Graph * this, size_t origin, size_t destination)
{
	Node_read(this->originNode, origin);
	Node_read(this->destinationNode, destination);

	size_t link = Net_createEntry(this->net, 0);
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

		Net_addGap(this->net, deletedOutgoingLink, 0);

	} else {

		deletedIncomingLink = Node_deleteOrigin(this->destinationNode, origin);

		if ( 0 == deletedIncomingLink ) {
			return;
		}

		Node_deleteOutgoingLink(this->originNode);

		Net_addGap(this->net, deletedIncomingLink, 0);

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
	if (Net_isHead(this->net, place)) {
		return 0;
	}
	
	if ( ! Net_isInside(this->net, place) ) {
		return 0;
	}
	
	Node_read(this->node, place);

	return Node_isNode(this->node);
}

void Graph_export(struct Graph * this, FILE * file)
{
	struct Export * export = Net_createExport(this->net);
	
	Export_write(export, file);
	
	Export_destruct(export);
}

void Graph_import(struct Graph * this, FILE * file)
{
	struct Import * import = Imports_make(this->imports);
	
	Import_read(import, file);
	
	Import_destruct(import);
}
