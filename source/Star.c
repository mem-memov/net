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

void Star_getNodeDestinations(struct Star * this, size_t outgoingLink, size_t * destinations, size_t length)
{
	size_t i;
	
	for (i = 0; i < length; i++) {
		
		Link_read(this->outgoingLink, outgoingLink);
		destinations[i] = Link_getOutgoingNode(this->outgoingLink);
		outgoingLink = Link_getNextOutgoing(this->outgoingLink);
		
		if ( 0 == outgoingLink && i != length) {
			exit(1);
		}
	}
	
	if ( 0 != outgoingLink ) {
		exit(1);
	}
}

void Star_getNodeOrigins(struct Star * this, size_t incomingLink, size_t * origins, size_t length)
{
	size_t i;
	
	for (i = 0; i < length; i++) {
		
		Link_read(this->incomingLink, incomingLink);
		origins[i] = Link_getIncomingNode(this->incomingLink);
		incomingLink = Link_getNextIncoming(this->incomingLink);
		
		if ( 0 == incomingLink && i != length) {
			exit(1);
		}
	}
	
	if ( 0 != incomingLink ) {
		exit(1);
	}
}

size_t Star_deleteOutgoingLink(struct Star * this, size_t outgoingStartLink, size_t destinationNode)
{
	size_t outgoingLink = Star_findOutgoingLink(this, outgoingStartLink, destinationNode);
	
	if ( 0 == outgoingLink ) {
		return 0;
	}
	
	Link_read(this->outgoingLink, outgoingLink);
	Link_delete(this->outgoingLink);
	
	return outgoingLink;
}