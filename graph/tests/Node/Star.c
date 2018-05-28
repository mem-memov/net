#include "../../source/Star.h"
#include <stdlib.h>

#define STAR_MAX_CALLS 1

struct Star
{
	char call;
	char * method[STAR_MAX_CALLS];
	size_t oldIncomingLink[STAR_MAX_CALLS];
	size_t newIncomingLink[STAR_MAX_CALLS];
	size_t oldOutgoingLink[STAR_MAX_CALLS];
	size_t newOutgoingLink[STAR_MAX_CALLS];
	size_t incomingLink[STAR_MAX_CALLS];
	size_t originNode[STAR_MAX_CALLS];
	size_t foundIncomingLink[STAR_MAX_CALLS];
	size_t outgoingLink[STAR_MAX_CALLS];
	size_t destinationNode[STAR_MAX_CALLS];
	size_t foundOutgoingLink[STAR_MAX_CALLS];
	size_t * destinations[STAR_MAX_CALLS];
	size_t * origins[STAR_MAX_CALLS];
	size_t length[STAR_MAX_CALLS];
	size_t outgoingStartLink[STAR_MAX_CALLS];
	size_t incomingStartLink[STAR_MAX_CALLS];
};

struct Star * Star_mock()
{
	struct Star * this = malloc(sizeof(struct Star));

	this->call = 0;
	
	char i;
	for (i = 0; i < STAR_MAX_CALLS; i++) {
		this->method[i] = "method not specified";
		this->oldIncomingLink[i] = 55555;
		this->newIncomingLink[i] = 55555;
		this->oldOutgoingLink[i] = 55555;
		this->newOutgoingLink[i] = 55555;
		this->incomingLink[i] = 55555;
		this->originNode[i] = 55555;
		this->foundIncomingLink[i] = 55555;
		this->outgoingLink[i] = 55555;
		this->destinationNode[i] = 55555;
		this->foundOutgoingLink[i] = 55555;
		this->destinations[i] = NULL;
		this->origins[i] = NULL;
		this->length[i] = 55555;
		this->outgoingStartLink[i] = 55555;
		this->incomingStartLink[i] = 55555;
	}

	return this;
}

void Star_destruct(struct Star * this)
{
	free(this);
	this = NULL;
}

void Star_addIncomingLink(struct Star * this, size_t oldIncomingLink, size_t newIncomingLink)
{
	this->method[this->call] = "Star_addIncomingLink";
	
	this->oldIncomingLink[this->call] = oldIncomingLink;
	this->newIncomingLink[this->call] = newIncomingLink;
	
	this->call++;
}

void Star_addOutgoingLink(struct Star * this, size_t oldOutgoingLink, size_t newOutgoingLink)
{
	this->method[this->call] = "Star_addOutgoingLink";
	
	this->oldOutgoingLink[this->call] = oldOutgoingLink;
	this->newOutgoingLink[this->call] = newOutgoingLink;
	
	this->call++;
}

size_t Star_findIncomingLink(struct Star * this, size_t incomingLink, size_t originNode)
{
	this->method[this->call] = "Star_findIncomingLink";
	
	this->incomingLink[this->call] = incomingLink;
	this->originNode[this->call] = originNode;
	
	size_t foundIncomingLink = this->foundIncomingLink[this->call];
	
	this->call++;
	
	return foundIncomingLink;
}

size_t Star_findOutgoingLink(struct Star * this, size_t outgoingLink, size_t destinationNode)
{
	this->method[this->call] = "Star_findOutgoingLink";
	
	this->outgoingLink[this->call] = outgoingLink;
	this->destinationNode[this->call] = destinationNode;
	
	size_t foundOutgoingLink = this->foundOutgoingLink[this->call];
	
	this->call++;
	
	return foundOutgoingLink;
}

void Star_getNodeDestinations(struct Star * this, size_t outgoingLink, size_t * destinations, size_t length)
{
	this->method[this->call] = "Star_getNodeDestinations";
	
	this->outgoingLink[this->call] = outgoingLink;
	destinations = this->destinations[this->call];
	this->length[this->call] = length;
	
	this->call++;
}

void Star_getNodeOrigins(struct Star * this, size_t incomingLink, size_t * origins, size_t length)
{
	this->method[this->call] = "Star_getNodeOrigins";
	
	this->incomingLink[this->call] = incomingLink;
	origins = this->origins[this->call];
	this->length[this->call] = length;
	
	this->call++;
}

size_t Star_deleteOutgoingLink(struct Star * this, size_t outgoingStartLink, size_t destinationNode)
{
	this->method[this->call] = "Star_deleteOutgoingLink";
	
	this->outgoingStartLink[this->call] = outgoingStartLink;
	this->destinationNode[this->call] = destinationNode;
	
	size_t outgoingLink = this->outgoingLink[this->call];
	
	this->call++;
	
	return outgoingLink;
}

size_t Star_deleteIncomingLink(struct Star * this, size_t incomingStartLink, size_t originNode)
{
	this->method[this->call] = "Star_deleteIncomingLink";
	
	this->incomingStartLink[this->call] = incomingStartLink;
	this->originNode[this->call] = originNode;
	
	size_t incomingLink = this->incomingLink[this->call];
	
	this->call++;
	
	return incomingLink;
}