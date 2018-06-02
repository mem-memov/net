#include "Graph.h"
#include "Boat.h"
#include "Factory.h"
#include "Export.h"
#include "Import.h"
#include "Link.h"
#include "Node.h"

struct Graph {
	unsigned char * bytes;
	struct Boat * boat;
	struct Factory * factory;
	
	// pool
	struct Node * node;
	struct Node * originNode;
	struct Node * destinationNode;
	struct Link * link;
};

struct Graph * Graph_construct(size_t graphSize, size_t placeSize)
{
	struct Graph * this = malloc(sizeof(struct Graph));
	
	if (graphSize < 1) {
		exit(0);
	}
	if (placeSize < 1) {
		exit(0);
	}

	size_t entrySize = 6;
	this->bytes = malloc(graphSize * entrySize * placeSize);
	
	this->factory = Factory_construct(this->bytes, graphSize, entrySize, placeSize);

	this->boat = Factory_makeBoat(this->factory);

	// pool
	this->node = Factory_makeNode(this->factory);
	this->originNode = Factory_makeNode(this->factory);
	this->destinationNode = Factory_makeNode(this->factory);
	this->link = Factory_makeLink(this->factory);
	
	Boat_create(this->boat, placeSize);

	return this;
}

void Graph_destruct(struct Graph * this)
{
	free(this->bytes);
	this->bytes = NULL;
	
	// fields
	Boat_destruct(this->boat);
	
	// pool
	Node_destruct(this->node);
	Node_destruct(this->originNode);
	Node_destruct(this->destinationNode);
	Link_destruct(this->link);
	
	// factories
	Factory_destruct(this->factory);
	
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
	struct Import * import = Factory_makeImport(this->factory);
	
	Import_read(import, file);
	
	Import_destruct(import);
}
