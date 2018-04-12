#include "Link.h"
#include <stdlib.h>
#include "Node.h"

struct Link * Link_construct(size_t * places)
{
	struct Link * this = malloc(sizeof(struct Link));
	
	this->places = places;

	return this;
}

void Link_destruct(struct Link * this)
{
	free(this);
}

void Link_create(struct Link * this, size_t place, struct Node * originNode, struct Node * destinationNode)
{
	this->inNode = Node_getPlace(destinationNode);
	this->places[place][0] = this->inNode;
	
	this->outPrevious = 0;
	this->places[place][1] = this->outPrevious;
	
	this->outNext = 0;
	this->places[place][2] = this->outNext;
	
			
	this->outNode = Node_getPlace(originNode);
	this->places[place][3] = this->outNode;
	
	this->inPrevious = 0;
	this->places[place][4] = this->inPrevious;
	
	this->inNext = 0;
	this->places[place][5] = this->inNext;
}

void Link_read(struct Link * this, size_t place)
{
	this->inNode = this->places[place][0];
	this->outPrevious = this->places[place][1];
	this->outNext = this->places[place][2];	
			
	this->outNode = this->places[place][3];
	this->inPrevious = this->places[place][4];
	this->inNext = this->places[place][5];
}