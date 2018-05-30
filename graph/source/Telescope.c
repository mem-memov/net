#include "Telescope.h"

struct Telescope
{
	struct Link * link;
};

struct Telescope * Telescope_construct(struct Link * link)
{
	struct Telescope * this = malloc(sizeof(struct Telescope));
	
	// pool
	this->link = link;

	return this;
}

void Telescope_destruct(struct Telescope * this)
{
	Link_destruct(this->link);
	
	free(this);
	this = NULL;
}

size_t Telescope_findIncomingLink(struct Telescope * this, size_t incomingLink, size_t originNode)
{
	do {
		Link_read(this->link, incomingLink);
		if ( Link_isIncomingFromNode(this->link, originNode) ) {
			return incomingLink;
		}
		incomingLink = Link_getNextIncoming(this->link);
	} while( 0 != incomingLink );
	
	return 0;
}

size_t Telescope_findOutgoingLink(struct Telescope * this, size_t outgoingLink, size_t destinationNode)
{
	do {
		Link_read(this->link, outgoingLink);
		if (Link_isOutgoingToNode(this->link, destinationNode)) {
			return outgoingLink;
		}
		outgoingLink = Link_getNextOutgoing(this->link);
	} while( 0 != outgoingLink );
	
	return 0;
}