#include "Node.h"
#include <stdlib.h>
#include "Link.h"
#include "NodeError.h"
#include "Place.h"

struct Node {
	struct Place * place;
	struct Place * data;
	struct Place * outgoingLinkCount;
	struct Place * incomingLinkCount;
	struct Place * outgoingLink;
	struct Place * incomingLink;
	struct Link * link;
	struct NodeError * error;
};

struct Node * Node_construct(
	struct Place * place,
	struct Place * data,
	struct Place * outgoingLinkCount,
	struct Place * incomingLinkCount,
	struct Place * outgoingLink,
	struct Place * incomingLink,
	struct Link * link,
	struct NodeError * error
) {
	struct Node * this = malloc(sizeof(struct Node));

	this->place = place;
	this->data = data;
	this->outgoingLinkCount = outgoingLinkCount;
	this->incomingLinkCount = incomingLinkCount;
	this->outgoingLink = outgoingLink;
	this->incomingLink = incomingLink;
	this->link = link;
	this->error = error;

	return this;
}

void Node_destruct(struct Node * this)
{
	Place_destruct(this->place);
	Place_destruct(this->data);
	Place_destruct(this->outgoingLinkCount);
	Place_destruct(this->incomingLinkCount);
	Place_destruct(this->outgoingLink);
	Place_destruct(this->incomingLink);
	Link_destruct(this->link);
	
	free(this);
	this = NULL;
}

void Node_bind(struct Node * this, size_t place)
{
	
	Place_bind(this->place, place + 0);
	Place_bind(this->data, place + 1);
	Place_bind(this->outgoingLinkCount, place + 2);
	Place_bind(this->incomingLinkCount, place + 3);
	Place_bind(this->outgoingLink, place + 4);
	Place_bind(this->incomingLink, place + 5);
}

void Node_create(struct Node * this, size_t place)
{
	Node_bind(this, place);

	Place_set(this->place, place);
	Place_set(this->data, 0);
	Place_set(this->outgoingLinkCount, 0);
	Place_set(this->incomingLinkCount, 0);
	Place_set(this->outgoingLink, 0);
	Place_set(this->incomingLink, 0);
}

void Node_read(struct Node * this, size_t place)
{
	Node_bind(this, place);
}

void Node_delete(struct Node * this)
{
	NodeError_forbidDeletingNodeWithConnections(this->error, Place_get(this->outgoingLink), Place_get(this->incomingLink));

	Place_set(this->place, 0);
	Place_set(this->data, 0);
}

size_t Node_getPlace(struct Node * this)
{
	return Place_get(this->place);
}

char Node_isNode(struct Node * this)
{
	if ( Place_keepsPosition(this->place) && ! Place_isZero(this->place) ) {
		return 1;
	}
	
	return 0;
}

char Node_hasIncomingLink(struct Node * this)
{
	if ( ! Place_isZero(this->incomingLink) ) {
		return 1;
	}
	
	return 0;
}

char Node_hasOutgoingLink(struct Node * this)
{
	if ( ! Place_isZero(this->outgoingLink) ) {
		return 1;
	}
	
	return 0;
}

void Node_addIncomingLink(struct Node * this, struct Link * link)
{
	if ( ! Node_hasIncomingLink(this)) {
		Link_shiftIncoming(link, Place_get(this->place));
	} else {
		Link_joinIncoming(link, Place_get(this->place), Place_get(this->incomingLink));
		Link_read(this->link, Place_get(this->incomingLink));
		Link_shiftIncoming(this->link, Link_getPlace(link));
	}
	
	Place_set(this->incomingLink, Link_getPlace(link));
	Place_increment(this->incomingLinkCount);
}

void Node_addOutgoingLink(struct Node * this, struct Link * link)
{
	if ( ! Node_hasOutgoingLink(this)) {
		Link_shiftOutgoing(link, Place_get(this->place));
	} else {
		Link_joinOutgoing(link, Place_get(this->place), Place_get(this->outgoingLink));
		Link_read(this->link, Place_get(this->outgoingLink));
		Link_shiftOutgoing(this->link, Link_getPlace(link));
	}
	
	Place_set(this->outgoingLink, Link_getPlace(link));
	Place_increment(this->outgoingLinkCount);
}

size_t Node_findIncomingLink(struct Node * this, size_t origin)
{
	if ( ! Node_hasIncomingLink(this)) {
		return 0;
	}

	size_t incomingLink = Place_get(this->incomingLink);
	
	do {
		Link_read(this->link, incomingLink);
		if (Link_isIncomingFromNode(this->link, origin)) {
			return incomingLink;
		}
		incomingLink = Link_getNextIncoming(this->link);
	} while( 0 != incomingLink );
	
	return 0;
}

size_t Node_findOutgoingLink(struct Node * this, size_t destination)
{
	if ( ! Node_hasOutgoingLink(this)) {
		return 0;
	}

	size_t outgoingLink = Place_get(this->outgoingLink);
	
	do {
		Link_read(this->link, outgoingLink);
		if (Link_isOutgoingToNode(this->link, destination)) {
			return outgoingLink;
		}
		outgoingLink = Link_getNextOutgoing(this->link);
	} while( 0 != outgoingLink );
	
	return 0;
}

char Node_hasMoreOutgoingLinks(struct Node * this)
{
	if ( Place_get(this->outgoingLinkCount) > Place_get(this->incomingLinkCount)) {
		return 1;
	}
	
	return 0;
}

void Node_readOutgoingLink(struct Node * this, struct Link * link)
{
	NodeError_forbidReadingOutgoingLinkWhenNonePresent(this->error, Place_get(this->outgoingLink));
	
	Link_read(link, Place_get(this->outgoingLink));
}

void Node_readIncomingLink(struct Node * this, struct Link * link)
{
	NodeError_forbidReadingIncomingLinkWhenNonePresent(this->error, Place_get(this->incomingLink));
	
	Link_read(link, Place_get(this->incomingLink));
}

void Node_deleteOutgoingLink(struct Node * this)
{
	NodeError_forbidDeletingOutgoingLinkWhenNonePresent(this->error, Place_get(this->outgoingLinkCount));
	
	Place_decrement(this->outgoingLinkCount);
	
	if ( Place_isZero(this->outgoingLinkCount) ) {
		Place_set(this->outgoingLink, 0);
	}
}

void Node_deleteIncomingLink(struct Node * this)
{
	NodeError_forbidDeletingIncomingLinkWhenNonePresent(this->error, Place_get(this->incomingLinkCount));
	
	Place_decrement(this->incomingLinkCount);
	
	if ( Place_isZero(this->incomingLinkCount) ) {
		Place_set(this->incomingLink, 0);
	}
}