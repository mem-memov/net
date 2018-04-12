#include "Space.h"
#include <stdlib.h>
#include <stdio.h>
#include "Gap.h"
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
	this->net = Net_construct(this->places, this->spaceSize, this->entrySize, this->placeSize);
	this->gap = NULL;
	
	Net_create(this->net);

	return this;
}

void Space_destruct(struct Space * this)
{
	if (NULL != this->gap) {
		Gap_destruct(this->gap);
	}
	
	free(this->places);
	
	free(this);
}

char Space_hasFreePlace(struct Space * this)
{
	if (this->places[0] < this->size) {
		return 1;
	}
	
	return 0;
}

size_t Space_addNode(struct Space * this)
{
	size_t place = Net_createEntry(this->net, this->gap);

	struct Node * node = Node_construct(this->places);
	
	Node_create(node, place);

	return place;
}

void Space_removeNode(struct Space * this, size_t place)
{
	size_t current;
	size_t next;
	
	// remove the node
	
	current = place;
	
	while (0 != this->places[current + 1]) {
		this->places[current] = 0;
		this->places[current + 1] = 0;
		
		if (NULL == this->gap) {
			this->gap = Gap_construct(current, NULL);
		} else {
			this->gap = Gap_construct(current, this->gap);
		}
		
		current = this->places[current + 1];
	}
	
	// remove connections to the node
	
	current = 1;
	
	while (current < this->places[0]) {
		
		next = this->places[current + 1];
		
		if (place == next) {
			this->places[current + 1] = this->places[next + 1];
			
			this->places[next] = 0;
			this->places[next + 1] = 0;

			if (NULL == this->gap) {
				this->gap = Gap_construct(next, NULL);
			} else {
				this->gap = Gap_construct(next, this->gap);
			}
		}
		
		current += 2;
	}
}

void Space_connectNodes(struct Space * this, size_t origin, size_t destination)
{
	struct Node * originNode = Node_construct(this->places);
	Node_read(originNode, origin);
	
	struct Node * destinationNode = Node_construct(this->places);
	Node_read(destinationNode, destination);
	
	if (Node_isSame(originNode, destinationNode)) {
		exit(1);
	}
	
	struct Link * link = Link_construct(this->places);
	
	size_t place = Net_createEntry(this->net, this->gap);
	
	Link_create(link, place, originNode, destinationNode);
	
	
	
	
	if (! Space_isNode(this, origin) || ! Space_isNode(this, destination)) {
		exit(1);
	}
	
	size_t last = origin;
	size_t place;

	while (0 != this->places[last + 1]) {
		last = this->places[last + 1];
	}

	struct Gap * gap = this->gap;
	if (NULL != gap) {
		this->places[last + 1] = Gap_getPlace(gap);
		this->gap = Gap_getNext(gap);
		Gap_destruct(gap);
	} else {
		this->places[last + 1] = this->places[0];
		this->places[0] += 2;
	}

	place = this->places[last + 1];
	
	this->places[place] = destination;
	this->places[place + 1] = 0;
}

void Space_disconnectNodes(struct Space * this, size_t origin, size_t destination)
{
	if (! Space_isNode(this, origin) || ! Space_isNode(this, destination)) {
		exit(1);
	}
	
	size_t current = origin;
	size_t next = this->places[origin + 1];

	while (this->places[next] != destination) {
		
		current = next;
		next = this->places[current + 1];
		
		if (next >= this->places[0]) {
			exit(1);
		}
	}
	
	this->places[current + 1] = this->places[next + 1];
	this->places[next] = 0;
	this->places[next + 1] = 0;
	
	if (NULL == this->gap) {
		this->gap = Gap_construct(next, NULL);
	} else {
		this->gap = Gap_construct(next, this->gap);
	}
}

size_t Space_getNode(struct Space * this, size_t next, size_t * place)
{
	* place = this->places[next];
	
	return this->places[next + 1];
}

char Space_isNode(struct Space * this, size_t place)
{
	if (this->places[place] == place && place > 0 && place < this->places[0]) {
		return 1;
	}

	return 0;
}

void Space_export(struct Space * this, FILE * file)
{
	size_t totalItems = fwrite(this->places, sizeof(size_t), this->places[0], file);
	
	if (totalItems != this->places[0]) {
		exit(1);
	}
}

void Space_import(struct Space * this, FILE * file)
{
	size_t headItems = fread(this->places, sizeof(size_t), 1, file);
	
	if (headItems != 1) {
		exit(1);
	}
	
	if (this->size < this->places[0]) {
		exit(1);
	}
	
	size_t bodyItems = fread(this->places + 1, sizeof(size_t), this->places[0] - 1, file);

	if (bodyItems != this->places[0] - 1) {
		exit(1);
	}
	
	size_t current = 1;
	
	while (current < this->places[0]) {
		
		if (0 == this->places[current] && 0 == this->places[current + 1]) {
			if (NULL == this->gap) {
				this->gap = Gap_construct(current, NULL);
			} else {
				this->gap = Gap_construct(current, this->gap);
			}
		}
		
		current += 2;
	}
}
