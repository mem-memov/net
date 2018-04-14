#include "Space.h"
#include <stdlib.h>
#include <stdio.h>
#include "Link.h"
#include "Net.h"
#include "Node.h"

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
	this->node = Node_construct(this->places);
	this->originNode = Node_construct(this->places);
	this->destinationNode = Node_construct(this->places);
	this->link = Link_construct(this->places);
	
	Net_create(this->net, this->placeSize);

	return this;
}

void Space_destruct(struct Space * this)
{
	free(this->places);
	free(this->net);
	
	free(this->node);
	free(this->originNode);
	free(this->destinationNode);
	free(this->link);
	
	free(this);
}

char Space_hasFreePlace(struct Space * this)
{
	return Net_hasSpaceForEntry(this->net);
}

size_t Space_addNode(struct Space * this)
{
	size_t place = Net_createEntry(this->net);
	
	Node_create(this->node, place);

	return place;
}

void Space_removeNode(struct Space * this, size_t place)
{
//	size_t current;
//	size_t next;
//	
//	// remove the node
//	
//	current = place;
//	
//	while (0 != this->places[current + 1]) {
//		this->places[current] = 0;
//		this->places[current + 1] = 0;
//		
//		if (NULL == this->gap) {
//			this->gap = Gap_construct(current, NULL);
//		} else {
//			this->gap = Gap_construct(current, this->gap);
//		}
//		
//		current = this->places[current + 1];
//	}
//	
//	// remove connections to the node
//	
//	current = 1;
//	
//	while (current < this->places[0]) {
//		
//		next = this->places[current + 1];
//		
//		if (place == next) {
//			this->places[current + 1] = this->places[next + 1];
//			
//			this->places[next] = 0;
//			this->places[next + 1] = 0;
//
//			if (NULL == this->gap) {
//				this->gap = Gap_construct(next, NULL);
//			} else {
//				this->gap = Gap_construct(next, this->gap);
//			}
//		}
//		
//		current += 2;
//	}
}

void Space_connectNodes(struct Space * this, size_t origin, size_t destination)
{
	Node_read(this->originNode, origin);
	Node_read(this->destinationNode, destination);

	size_t link = Net_createEntry(this->net);
	Link_create(this->link, link, origin, destination);

	Node_addOutgoingLink(this->originNode, this->link);
	Node_addIncomingLink(this->destinationNode, this->link);
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
}

size_t Space_getOutgoingNodes(struct Space * this, size_t next, size_t * place)
{
	if ( next == (*place) ) {
		Node_read(this->node, next);
		Node_readOutgoingLink(this->node, this->link);
		(*place) = Link_getOutgoingNode(this->link);
	} else {
		Link_read(this->link, next);
		(*place) = Link_getOutgoingNode(this->link);
	}

	return Link_getNextOutgoing(this->link);
}

char Space_isNode(struct Space * this, size_t place)
{
	if (Net_isHead(this->net, place)) {
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
