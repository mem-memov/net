#include "../source/Link.h"
#include <stdlib.h>

#define LINK_MAX_CALLS 6

struct Link {
	char call;
	char * method[LINK_MAX_CALLS];
	size_t place[LINK_MAX_CALLS];
	size_t previousIncomingLink[LINK_MAX_CALLS];
	size_t previousOutgoingLink[LINK_MAX_CALLS];
	size_t nextIncomingLink[LINK_MAX_CALLS];
	size_t nextOutgoingLink[LINK_MAX_CALLS];
	size_t originNode[LINK_MAX_CALLS];
	size_t destinationNode[LINK_MAX_CALLS];
	char isOutgoingToNode[LINK_MAX_CALLS];
	char isIncomingFromNode[LINK_MAX_CALLS];
};

struct Link * Link_mock()
{
	struct Link * this = malloc(sizeof(struct Link));

	this->call = 0;
	
	char i;
	for (i = 0; i < LINK_MAX_CALLS; i++) {
		this->method[i] = "method never called";
		this->place[i] = 55555;
		this->previousIncomingLink[i] = 55555;
		this->previousOutgoingLink[i] = 55555;
		this->nextIncomingLink[i] = 55555;
		this->nextOutgoingLink[i] = 55555;
		this->originNode[i] = 55555;
		this->destinationNode[i] = 55555;
		this->isOutgoingToNode[i] = 31;
		this->isIncomingFromNode[i] = 31;
	}
	
	return this;
}

void Link_destruct(struct Link * this)
{
	free(this);
	this = NULL;
}

size_t Link_getPlace(struct Link * this)
{
	this->method[this->call] = "Link_getPlace";
	
	size_t place = this->place[this->call];
		
	this->call++;
	
	return place;
}

void Link_create(struct Link * this, size_t place, size_t origin, size_t destination)
{
	this->method[this->call] = "Link_create";
	this->place[this->call] = place;
	this->originNode[this->call] = origin;
	this->destinationNode[this->call] = destination;
	
	this->call++;
}

void Link_read(struct Link * this, size_t place)
{
	this->method[this->call] = "Link_read";
	this->place[this->call] = place;
	
	this->call++;
}

void Link_joinOutgoing(struct Link * this, size_t previous, size_t next)
{
	this->method[this->call] = "Link_joinOutgoing";
	this->previousOutgoingLink[this->call] = previous;
	this->nextOutgoingLink[this->call] = next;
	
	this->call++;
}

void Link_joinIncoming(struct Link * this, size_t previous, size_t next)
{
	this->method[this->call] = "Link_joinIncoming";
	this->previousIncomingLink[this->call] = previous;
	this->nextIncomingLink[this->call] = next;
	
	this->call++;
}

void Link_shiftOutgoing(struct Link * this, size_t previous)
{
	this->method[this->call] = "Link_shiftOutgoing";
	this->previousOutgoingLink[this->call] = previous;
	
	this->call++;
}

void Link_shiftIncoming(struct Link * this, size_t previous)
{
	this->method[this->call] = "Link_shiftIncoming";
	this->previousIncomingLink[this->call] = previous;
	
	this->call++;
}

char Link_isOutgoingToNode(struct Link * this, size_t destination)
{
	this->method[this->call] = "Link_isOutgoingToNode";
	this->destinationNode[this->call] = destination;
	
	char isOutgoingToNode = this->isOutgoingToNode[this->call];
		
	this->call++;
	
	if (1 == isOutgoingToNode) {
		return 1;
	} 
	
	if (0 == isOutgoingToNode) {
		return 0;
	}
}

char Link_isIncomingFromNode(struct Link * this, size_t origin)
{
	this->method[this->call] = "Link_isIncomingFromNode";
	this->originNode[this->call] = origin;
	
	char isIncomingFromNode = this->isIncomingFromNode[this->call];

	this->call++;
	
	return isIncomingFromNode;
}

size_t Link_getNextOutgoing(struct Link * this)
{
	this->method[this->call] = "Link_getNextOutgoing";
	size_t nextOutgoingLink = this->nextOutgoingLink[this->call];
	
	this->call++;
	
	return nextOutgoingLink;
}

size_t Link_getNextIncoming(struct Link * this)
{
	this->method[this->call] = "Link_getNextIncoming";
	size_t nextIncomingLink = this->nextIncomingLink[this->call];
	
	this->call++;
	
	return nextIncomingLink;
}

void Link_delete(struct Link * this)
{
	this->method[this->call] = "Link_delete";
	
	this->call++;
}

size_t Link_getOutgoingNode(struct Link * this)
{
	this->method[this->call] = "Link_getOutgoingNode";
	
	size_t outgoingNode = this->destinationNode[this->call];
	
	this->call++;
	
	return outgoingNode;
}

size_t Link_getIncomingNode(struct Link * this)
{
	this->method[this->call] = "Link_getIncomingNode";
	
	size_t incomingNode = this->originNode[this->call];
	
	this->call++;
	
	return incomingNode;
}