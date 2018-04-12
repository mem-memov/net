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
	
    this->incomingNode = this->places[place] + 0;
    this->outgoingPrevious = this->places[place] + 1;
    this->outgoingNext = this->places[place] + 2;
    this->outgoingNode = this->places[place] + 3;
    this->incomingPrevious = this->places[place] + 4;
    this->incomingNext = this->places[place] + 5;
}

size_t Link_getPlace(struct Node * this)
{
	return this->place;
}

void Link_create(struct Link * this, size_t place, size_t origin, size_t destination)
{
	Link_bind(struct Link * this, size_t place);
	
	(*this->incomingNode) = destination;
	(*this->outgoingPrevious) = 0;
	(*this->outgoingNext) = 0;
	(*this->outgoingNode) = origin;
	(*this->incomingPrevious) = 0;	
	(*this->incomingNext) = 0;
}

void Link_joinOutgoingChain(struct Link * this, size_t previous, size_t next)
{
	(*this->outgoingPrevious) = previous;
	(*this->outgoingNext) = next;
}

void Link_joinIncomingChain(struct Link * this, size_t previous, size_t next)
{
	(*this->incomingPrevious) = previous;
	(*this->incomingNext) = next;
}

void Link_append(struct Link * this, size_t previous)
{
	
}

void Link_read(struct Link * this, size_t place)
{
	Link_bind(struct Link * this, size_t place);
}