#include "Star.h"

struct Star
{
	struct Link * incomingLink;
	struct Link * outgoingLink;
	struct Telescope * telescope;
	struct StarError * error;
};

struct Star * Star_construct(
	struct Link * incomingLink, 
	struct Link * outgoingLink,
	struct Telescope * telescope,
	struct StarError * error
) {
	struct Star * this = malloc(sizeof(struct Star));

	// pool
	this->incomingLink = incomingLink;
	this->outgoingLink = outgoingLink;
	
	this->telescope = telescope;
	
	this->error = error;

	return this;
}

void Star_destruct(struct Star * this)
{
	Link_destruct(this->incomingLink);
	Link_destruct(this->outgoingLink);
	
	Telescope_destruct(this->telescope);
	
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

void Star_getNodeDestinations(struct Star * this, size_t outgoingLink, size_t * destinations, size_t length)
{
	size_t index;
	size_t maxIndex = length - 1;
	
	for (index = 0; index <= maxIndex; index++) {
		
		Link_read(this->outgoingLink, outgoingLink);
		
		destinations[index] = Link_getOutgoingNode(this->outgoingLink);
		
		outgoingLink = Link_getNextOutgoing(this->outgoingLink);
		
		StarError_forbidShortDestinationList(this->error, outgoingLink, index, maxIndex);
	}
	
	StarError_forbidLongDestinationList(this->error, outgoingLink);
}

void Star_getNodeOrigins(struct Star * this, size_t incomingLink, size_t * origins, size_t length)
{
	size_t index;
	size_t maxIndex = length - 1;
	
	for (index = 0; index <= maxIndex; index++) {
		
		Link_read(this->incomingLink, incomingLink);
		
		origins[index] = Link_getIncomingNode(this->incomingLink);
		
		incomingLink = Link_getNextIncoming(this->incomingLink);
		
		StarError_forbidShortOriginList(this->error, incomingLink, index, maxIndex);
	}
	
	StarError_forbidLongOriginList(this->error, incomingLink);
}

size_t Star_deleteOutgoingLink(struct Star * this, size_t outgoingStartLink, size_t destinationNode)
{
	size_t outgoingLink = Telescope_findOutgoingLink(this->telescope, outgoingStartLink, destinationNode);
	
	if ( 0 == outgoingLink ) {
		return 0;
	}
	
	Link_read(this->outgoingLink, outgoingLink);
	Link_delete(this->outgoingLink);
	
	return outgoingLink;
}

size_t Star_deleteIncomingLink(struct Star * this, size_t incomingStartLink, size_t originNode)
{
	size_t incomingLink = Telescope_findIncomingLink(this->telescope, incomingStartLink, originNode);
	
	if ( 0 == incomingLink ) {
		return 0;
	}
	
	Link_read(this->incomingLink, incomingLink);
	Link_delete(this->incomingLink);
	
	return incomingLink;
}