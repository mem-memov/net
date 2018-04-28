#include "Space.h"
#include <stdlib.h>
#include <stdio.h>
#include "Link.h"
#include "Net.h"
#include "Node.h"

struct Space {
	size_t spaceSize;
	size_t entrySize;
	size_t placeSize;
	size_t * places;
	struct Net * net;

	struct DirectionError * directionError;
	struct NodeError * nodeError;
	
	struct Node * node;
	struct Node * originNode;
	struct Node * destinationNode;
	struct Link * link;
};

struct Space * Space_construct(size_t spaceSize)
{
	struct Space * this = malloc(sizeof(struct Space));
	
	if (spaceSize < 1) {
		exit(0);
	}
	
	this->spaceSize = spaceSize;
	this->entrySize = 6;
	this->placeSize = sizeof(size_t);
	this->places = (size_t *)malloc(this->spaceSize * this->entrySize * this->placeSize);
	this->net = Net_construct(this->places, this->spaceSize, this->entrySize);

	// pool
	this->directionError = DirectionError_construct();
	this->nodeError = NodeError_construct();
	this->node = Node_construct(
		this->places, 
		Link_construct(
			this->places,
			Direction_constructOutgoing(
				this->places,
				this->directionError
			),
			Direction_constructIncoming(
				this->places,
				this->directionError
			)
		),
		this->nodeError
	);
	this->originNode = Node_construct(
		this->places, 
		Link_construct(
			this->places,
			Direction_constructOutgoing(
				this->places,
				this->directionError
			),
			Direction_constructIncoming(
				this->places,
				this->directionError
			)
		),
		this->nodeError
	);
	this->destinationNode = Node_construct(
		this->places, 
		Link_construct(
			this->places,
			Direction_constructOutgoing(
				this->places,
				this->directionError
			),
			Direction_constructIncoming(
				this->places,
				this->directionError
			)
		),
		this->nodeError
	);
	this->link = Link_construct(
		this->places,
		Direction_constructOutgoing(
			this->places,
			this->directionError
		),
		Direction_constructIncoming(
			this->places,
			this->directionError
		)
	);
	
	Net_create(this->net, this->placeSize);

	return this;
}

void Space_destruct(struct Space * this)
{
	free(this->places);
	this->places = NULL;
	
	Net_destruct(this->net);
	
	Node_destruct(this->node);
	Node_destruct(this->originNode);
	Node_destruct(this->destinationNode);
	Link_destruct(this->link);
	NodeError_destruct(this->nodeError);
	DirectionError_destruct(this->directionError);
	
	free(this);
	this = NULL;
}

char Space_hasFreePlace(struct Space * this)
{
	return Net_hasSpaceForEntry(this->net);
}

size_t Space_addNode(struct Space * this)
{
	size_t place = Net_createEntry(this->net);
	
	Node_create(this->node, place);
	
	Net_incrementNodes(this->net);

	return place;
}

void Space_removeNode(struct Space * this, size_t place)
{
	size_t link;
	size_t node;

	link = 0;
	node = 0;
	do {
		Space_getOutgoingNodes(this, &place, &link, &node);
		if ( 0 != node) {
			Space_disconnectNodes(this, place, node);
		}
	} while (0 != link);

	link = 0;
	node = 0;
	do {
		Space_getIncomingNodes(this, &place, &link, &node);
		if ( 0 != node) {
			Space_disconnectNodes(this, node, place);
		}
	} while (0 != link);
	
	Node_read(this->node, place);
	Node_delete(this->node);
	
	Net_decrementNodes(this->net);
	
	Net_addGap(this->net, place);
}

void Space_connectNodes(struct Space * this, size_t origin, size_t destination)
{
	Node_read(this->originNode, origin);
	Node_read(this->destinationNode, destination);

	size_t link = Net_createEntry(this->net);
	Link_create(this->link, link, origin, destination);

	Node_addOutgoingLink(this->originNode, this->link);
	Node_addIncomingLink(this->destinationNode, this->link);
	
	Net_incrementLinks(this->net);
}

void Space_disconnectNodes(struct Space * this, size_t origin, size_t destination)
{
	Node_read(this->originNode, origin);
	Node_read(this->destinationNode, destination);
	
	size_t link = Node_findOutgoingLink(this->originNode, destination);
	
	if (0 == link) {
		return;
	}
	
	Link_read(this->link, link);
	Link_delete(this->link);
	
	Net_addGap(this->net, link);
	
	Node_deleteOutgoingLink(this->originNode);
	Node_deleteIncomingLink(this->destinationNode);
	
	Net_decrementLinks(this->net);
}

void Space_getOutgoingNodes(struct Space * this, const size_t * origin, size_t * link, size_t * target)
{
	if ( 0 == (*link) && 0 == (*target)) { // starting point
		Node_read(this->node, (*origin));
		if ( ! Node_hasOutgoingLink(this->node) ) {
			return;
		}
		Node_readOutgoingLink(this->node, this->link);
	} else {
		Link_read(this->link, (*link));
	}
	
	(*link) = Link_getNextOutgoing(this->link);
	(*target) = Link_getOutgoingNode(this->link);
}

void Space_getIncomingNodes(struct Space * this, const size_t * target, size_t * link, size_t * origin)
{
	if ( 0 == (*link) && 0 == (*origin)) { // starting point
		Node_read(this->node, (*target));
		if ( ! Node_hasIncomingLink(this->node) ) {
			return;
		}
		Node_readIncomingLink(this->node, this->link);
	} else {
		Link_read(this->link, (*link));
	}
	
	(*link) = Link_getNextIncoming(this->link);
	(*origin) = Link_getIncomingNode(this->link);
}

char Space_isNode(struct Space * this, size_t place)
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

void Space_export(struct Space * this, FILE * file)
{
	Net_export(this->net, file);
}

void Space_import(struct Space * this, FILE * file)
{
	size_t headPlaces = fread(this->places, this->placeSize, this->entrySize, file);
	
	if (headPlaces != this->entrySize) {
		exit(1);
	}
	
	Net_read(this->net);
	
	if (Net_isSpaceCut(this->net)) {
		exit(1);
	}
	
	Net_import(this->net, file);
}
