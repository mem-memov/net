#include "Link.h"
#include <stdlib.h>
#include "Direction.h"

struct Link {
	size_t * places;
        
	size_t place;
	
	// pool
	struct Direction * outgoing;
	struct Direction * incoming;	
};

struct Link * Link_construct(size_t * places, struct Direction * outgoing, struct Direction * incoming)
{
	struct Link * this = malloc(sizeof(struct Link));
	
	this->places = places;

	// pool
	this->outgoing = outgoing;
	this->incoming = incoming;

	return this;
}

void Link_destruct(struct Link * this)
{
	Direction_destruct(this->outgoing);
	Direction_destruct(this->incoming);
	
	free(this);
	this = NULL;
}

size_t Link_getPlace(struct Link * this)
{
	return this->place;
}

void Link_create(struct Link * this, size_t place, size_t origin, size_t destination)
{
	if (origin == destination) {
		exit(1);
	}
	
	this->place = place;
	
	Direction_create(this->outgoing, place, destination);
	Direction_create(this->incoming, place, origin);
}

void Link_read(struct Link * this, size_t place)
{
	this->place = place;
	
	Direction_read(this->outgoing, this->place);
	Direction_read(this->incoming, this->place);
}

void Link_joinOutgoing(struct Link * this, size_t previous, size_t next)
{
	Direction_joinChain(this->outgoing, previous, next);
}

void Link_joinIncoming(struct Link * this, size_t previous, size_t next)
{
	Direction_joinChain(this->incoming, previous, next);
}

void Link_shiftOutgoing(struct Link * this, size_t previous)
{
	Direction_append(this->outgoing, previous);
}

void Link_shiftIncoming(struct Link * this, size_t previous)
{
	Direction_append(this->incoming, previous);
}

char Link_isOutgoingToNode(struct Link * this, size_t destination)
{
	return Direction_hasNode(this->outgoing, destination);
}

char Link_isIncomingFromNode(struct Link * this, size_t origin)
{
	return Direction_hasNode(this->incoming, origin);
}

size_t Link_getNextOutgoing(struct Link * this)
{
	return Direction_getNext(this->outgoing);
}

size_t Link_getNextIncoming(struct Link * this)
{
	return Direction_getNext(this->incoming);
}

void Link_delete(struct Link * this)
{
	Direction_delete(this->outgoing);
	Direction_delete(this->incoming);
}

size_t Link_getOutgoingNode(struct Link * this)
{
	return Direction_getNode(this->outgoing);
}

size_t Link_getIncomingNode(struct Link * this)
{
	return Direction_getNode(this->incoming);
}