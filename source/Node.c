#include "Node.h"
#include <stdlib.h>

struct Node {
	// fields
	struct Place * place;
	struct Place * data;
	struct Count * outgoingLinkCount;
	struct Count * incomingLinkCount;
	struct Place * outgoingLink;
	struct Place * incomingLink;
	
	// pool
	struct Link * link;
	
	// error
	struct NodeError * error;
};

struct Node * Node_construct(
	struct Place * place,
	struct Place * data,
	struct Count * outgoingLinkCount,
	struct Count * incomingLinkCount,
	struct Place * outgoingLink,
	struct Place * incomingLink,
	struct Link * link,
	struct NodeError * error
) {
	struct Node * this = malloc(sizeof(struct Node));

	// fields
	this->place = place;
	this->data = data;
	this->outgoingLinkCount = outgoingLinkCount;
	this->incomingLinkCount = incomingLinkCount;
	this->outgoingLink = outgoingLink;
	this->incomingLink = incomingLink;
	
	this->link = link;
	
	// pool
	this->error = error;

	// error
	return this;
}

void Node_destruct(struct Node * this)
{
	Place_destruct(this->place);
	Place_destruct(this->data);
	Count_destruct(this->outgoingLinkCount);
	Count_destruct(this->incomingLinkCount);
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
	Count_bind(this->outgoingLinkCount, place + 2);
	Count_bind(this->incomingLinkCount, place + 3);
	Place_bind(this->outgoingLink, place + 4);
	Place_bind(this->incomingLink, place + 5);
}

void Node_create(struct Node * this, size_t place)
{
	Node_bind(this, place);

	Place_set(this->place, place);
	Place_set(this->data, 0);
	Count_create(this->outgoingLinkCount);
	Count_create(this->incomingLinkCount);
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
	Count_delete(this->outgoingLinkCount);
	Count_delete(this->incomingLinkCount);
}

size_t Node_getPlace(struct Node * this)
{
	return Place_get(this->place);
}

char Node_isNode(struct Node * this)
{
	if ( Place_keepsPosition(this->place) && 0 != Place_get(this->place) ) {
		return 1;
	}
	
	return 0;
}

char Node_hasIncomingLink(struct Node * this)
{
	if ( 0 != Place_get(this->incomingLink) ) {
		return 1;
	}
	
	return 0;
}

char Node_hasOutgoingLink(struct Node * this)
{
	if ( 0 != Place_get(this->outgoingLink) ) {
		return 1;
	}
	
	return 0;
}

void Node_addIncomingLink(struct Node * this, struct Link * link)
{
	if ( ! Node_hasIncomingLink(this)) {
		Link_shiftIncoming(
			link, 
			Place_get(this->place)
		);
	} else {
		Link_joinIncoming(
			link, 
			Place_get(this->place), 
			Place_get(this->incomingLink)
		);
		Link_read(
			this->link, 
			Place_get(this->incomingLink)
		);
		Link_shiftIncoming(
			this->link, 
			Link_getPlace(link)
		);
	}
	
	Place_set(
		this->incomingLink, 
		Link_getPlace(link)
	);
	Count_increment(this->incomingLinkCount);
}

void Node_addOutgoingLink(struct Node * this, struct Link * link)
{
	if ( ! Node_hasOutgoingLink(this)) {
		Link_shiftOutgoing(
			link, 
			Place_get(this->place)
		);
	} else {
		Link_joinOutgoing(
			link, 
			Place_get(this->place), 
			Place_get(this->outgoingLink)
		);
		Link_read(
			this->link, 
			Place_get(this->outgoingLink)
		);
		Link_shiftOutgoing(
			this->link, 
			Link_getPlace(link)
		);
	}
	
	Place_set(
		this->outgoingLink, 
		Link_getPlace(link)
	);
	Count_increment(this->outgoingLinkCount);
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
	if ( Count_get(this->outgoingLinkCount) > Count_get(this->incomingLinkCount)) {
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
	NodeError_forbidDeletingOutgoingLinkWhenNonePresent(this->error, Count_get(this->outgoingLinkCount));
	
	Count_decrement(this->outgoingLinkCount);
	
	if ( Count_isZero(this->outgoingLinkCount) ) {
		Place_set(this->outgoingLink, 0);
	}
}

void Node_deleteIncomingLink(struct Node * this)
{
	NodeError_forbidDeletingIncomingLinkWhenNonePresent(this->error, Count_get(this->incomingLinkCount));
	
	Count_decrement(this->incomingLinkCount);
	
	if ( Count_isZero(this->incomingLinkCount) ) {
		Place_set(this->incomingLink, 0);
	}
}