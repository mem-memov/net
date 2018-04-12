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

void Link_bind(struct Link * this, size_t place)
{
	this->place = place;
	
    this->inNode = this->places[place] + 0;
    this->outPreviou = this->places[place] + 1;
    this->outNext = this->places[place] + 2;
    this->outNode = this->places[place] + 3;
    this->inPrevious = this->places[place] + 4;
    this->inNext = this->places[place] + 5;
}

size_t Link_getPlace(struct Node * this)
{
	return this->place;
}

void Link_create(struct Link * this, size_t place, struct Node * originNode, struct Node * destinationNode)
{
	Link_bind(struct Link * this, size_t place);
	
	(*this->inNode) = Node_getPlace(destinationNode);
	(*this->outPrevious) = 0;
	(*this->outNext) = 0;
	(*this->outNode) = Node_getPlace(originNode);
	(*this->inPrevious) = 0;	
	(*this->inNext) = 0;
	
	Node_addOutLink(originNode, this);
	Node_addInLink(originNode, this);
}

void Link_read(struct Link * this, size_t place)
{
	Link_bind(struct Link * this, size_t place);
}