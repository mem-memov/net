#include "Link.h"
#include <stdlib.h>
#include "Incoming.h"
#include "Node.h"
#include "Outgoing.h"

struct Link * Link_construct(size_t * places)
{
	struct Link * this = malloc(sizeof(struct Link));
	
	this->places = places;

	// pool
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

void Link_read(struct Link * this, size_t place)
{
	this->place = place;
	
	Outgoing_read(this->outgoing, this->place);
	Incoming_read(this->incoming, this->place);
}

void Link_joinOutgoing(struct Link * this, size_t previous, size_t next)
{
	Outgoing_joinChain(this->outgoing, previous, next);
}

void Link_joinIncoming(struct Link * this, size_t previous, size_t next)
{
	Incoming_joinChain(this->incoming, previous, next);
}

void Link_shiftOutgoing(struct Link * this, size_t previous)
{
	Outgoing_append(this->outgoing, previous);
}

void Link_shiftIncoming(struct Link * this, size_t previous)
{
	Incoming_append(this->incoming, previous);
}

char Link_isOutgoingToNode(struct Link * this, size_t destination)
{
	return Outgoing_hasNode(this->outgoing, destination);
}

char Link_isIncomingFromNode(struct Link * this, size_t origin)
{
	return Incoming_hasNode(this->incoming, origin);
}

size_t Link_getNextOutgoing(struct Link * this)
{
	return Outgoing_getNext(this->outgoing);
}

size_t Link_getNextIncoming(struct Link * this)
{
	return Incoming_getNext(this->incoming);
}

void Link_delete(struct Link * this)
{
	
}

size_t Link_getOutgoingNode(struct Link * this)
{
	return Outgoing_getNode(this->outgoing);
}