#include "Star.h"
#include <stdlib.h>
#include "Link.h"

struct Star
{
	struct Link * incomingLink;
	struct Link * outgoingLink;
};

struct Star * Star_construct(struct Link * incomingLink, struct Link * outgoingLink)
{
	struct Star * this = malloc(sizeof(struct Star));

	// pool
	this->incomingLink = incomingLink;
	this->outgoingLink = outgoingLink;

	return this;
}

void Star_destruct(struct Star * this)
{
	Link_destruct(this->incomingLink);
	Link_destruct(this->outgoingLink);
	
	free(this);
	this = NULL;
}

void Star_addIncomingLink(struct Star * this, size_t oldIncomingLink, size_t newIncomingLink)
{
	Link_read(
		this->incomingLink, 
		oldIncomingLink
	);
	Link_shiftIncoming(
		this->incomingLink, 
		newIncomingLink
	);
}

void Star_addOutgoingLink(struct Star * this, size_t oldOutgoingLink, size_t newOutgoingLink)
{
	Link_read(
		this->outgoingLink, 
		oldOutgoingLink
	);
	Link_shiftOutgoing(
		this->outgoingLink, 
		newOutgoingLink
	);
}

size_t Star_findIncomingLink(struct Star * this, size_t incomingLink, size_t originNode)
{
	do {
		Link_read(this->incomingLink, incomingLink);
		if (Link_isIncomingFromNode(this->incomingLink, originNode)) {
			return incomingLink;
		}
		incomingLink = Link_getNextIncoming(this->incomingLink);
	} while( 0 != incomingLink );
	
	return 0;
}

size_t Star_findOutgoingLink(struct Star * this, size_t outgoingLink, size_t destinationNode)
{
	do {
		Link_read(this->outgoingLink, outgoingLink);
		if (Link_isOutgoingToNode(this->outgoingLink, destinationNode)) {
			return outgoingLink;
		}
		outgoingLink = Link_getNextOutgoing(this->outgoingLink);
	} while( 0 != outgoingLink );
	
	return 0;
}