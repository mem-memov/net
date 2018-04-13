#include "Link.h"
#include <stdlib.h>
#include "Node.h"

struct Link * Link_construct(size_t * places)
{
	struct Link * this = malloc(sizeof(struct Link));
	
	this->places = places;
	
	// pool
	this->originNode = Node_construct(this->places);
	this->destinationNode = Node_construct(this->places);
	this->outgoing = Outgoing_construct(this->places);
	this->previousOutgoing = Outgoing_construct(this->places);
	this->nextOutgoing = Outgoing_construct(this->places);
	this->incoming = Incoming_construct(this->places);
	this->previousIncoming = Incoming_construct(this->places);
	this->nextIncoming = Incoming_construct(this->places);

	return this;
}

void Link_destruct(struct Link * this)
{
	free(this);
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
	
	Outgoing_create(this->outgoing, place, destination);
	Incoming_create(this->incoming, place, origin);
}

void Link_joinOutgoing(struct Link * this, size_t previous, size_t next)
{
	(*this->outgoingPrevious) = previous;
	(*this->outgoingNext) = next;
}

void Link_joinIncoming(struct Link * this, size_t previous, size_t next)
{
	(*this->incomingPrevious) = previous;
	(*this->incomingNext) = next;
}

void Link_moveBackwardsInOutgoing(struct Link * this, size_t previous)
{
	(*this->outgoingPrevious) = previous;
}

void Link_moveBackwardsInIncoming(struct Link * this, size_t previous)
{
	(*this->incomingPrevious) = previous;
}

void Link_read(struct Link * this, size_t place)
{
	this->place = place;
}

char Link_isOutgoingToNode(struct Link * this, size_t destination)
{
	if ( (*this->incomingNode) == destination) {
		return 1;
	}
	
	return 0;
}

char Link_isLastOutgoing(struct Link * this)
{
	if ( (*this->outgoingNext) == 0) {
		return 1;
	}
	
	return 0;
}

void Link_delete(struct Link * this)
{
	
}