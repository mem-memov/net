#include "Node.h"
#include <stdlib.h>
#include "Link.h"

struct Node {
	size_t * place;
	size_t * data;
	size_t * outgoingLinkCount;
	size_t * incomingLinkCount;
	size_t * outgoingLink;
	size_t * incomingLink;
        
	size_t * places;
	
	struct Link * link;
};

struct Node * Node_construct(size_t * places)
{
	struct Node * this = malloc(sizeof(struct Node));

	this->places = places;
	
	// pool
	this->link = Link_construct(places);

	return this;
}

void Node_destruct(struct Node * this)
{
	free(this->link);
	
	free(this);
}

void Node_bind(struct Node * this, size_t place)
{
	this->place = this->places + place + 0;
	this->data = this->places + place + 1;
	this->outgoingLinkCount = this->places + place + 2;
	this->incomingLinkCount = this->places + place + 3;
	this->outgoingLink = this->places + place + 4;
	this->incomingLink = this->places + place + 5;	
}

void Node_create(struct Node * this, size_t place)
{
	Node_bind(this, place);

	(*this->place) = place;
	(*this->data) = 0;
	(*this->outgoingLinkCount) = 0;
	(*this->incomingLinkCount) = 0;
	(*this->outgoingLink) = 0;
	(*this->incomingLink) = 0;
}

void Node_read(struct Node * this, size_t place)
{
	Node_bind(this, place);
}

void Node_delete(struct Node * this)
{
	if ( 0 != (*this->outgoingLinkCount) || 0 != (*this->incomingLinkCount) || 0 != (*this->outgoingLink) || 0 != (*this->incomingLink) ) {
		exit(1);
	}

	(*this->place) = 0;
	(*this->data) = 0;
}

size_t Node_getPlace(struct Node * this)
{
	return (*this->place);
}

char Node_isNode(struct Node * this)
{
	if ( this->places[(*this->place)] == (*this->place) && 0 != (*this->place) ) {
		return 1;
	}
	
	return 0;
}

char Node_isSame(struct Node * this, struct Node * that)
{
	if ( (*this->place) == Node_getPlace(that) ) {
		return 1;
	}
	
	return 0;
}

char Node_hasIncomingLink(struct Node * this)
{
	if ( (*this->incomingLink) != 0 ) {
		return 1;
	}
	
	return 0;
}


char Node_hasOutgoingLink(struct Node * this)
{
	if ( (*this->outgoingLink) != 0 ) {
		return 1;
	}
	
	return 0;
}

void Node_addIncomingLink(struct Node * this, struct Link * link)
{
	if ( ! Node_hasIncomingLink(this)) {
		Link_joinIncoming(link, (*this->place), 0);
	} else {
		Link_joinIncoming(link, (*this->place), (*this->incomingLink));
		Link_read(this->link, (*this->incomingLink));
		Link_shiftIncoming(this->link, Link_getPlace(link));
	}
	
	(*this->incomingLink) = Link_getPlace(link);
	(*this->incomingLinkCount) += 1;
}

void Node_addOutgoingLink(struct Node * this, struct Link * link)
{
	if ( ! Node_hasOutgoingLink(this)) {
		Link_joinOutgoing(link, (*this->place), 0);
	} else {
		Link_joinOutgoing(link, (*this->place), (*this->outgoingLink));
		Link_read(this->link, (*this->outgoingLink));
		Link_shiftOutgoing(this->link, Link_getPlace(link));
	}
	
	(*this->outgoingLink) = Link_getPlace(link);
	(*this->outgoingLinkCount) += 1;
}

size_t Node_findIncomingLink(struct Node * this, size_t origin)
{
	if ( ! Node_hasIncomingLink(this)) {
		return 0;
	}

	size_t incomingLink = (*this->incomingLink);
	
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

	size_t outgoingLink = (*this->outgoingLink);
	
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
	if ( (*this->outgoingLinkCount) > (*this->incomingLinkCount)) {
		return 1;
	}
	
	return 0;
}

void Node_readOutgoingLink(struct Node * this, struct Link * link)
{
	Link_read(link, (*this->outgoingLink));
}

void Node_readIncomingLink(struct Node * this, struct Link * link)
{
	Link_read(link, (*this->incomingLink));
}

void Node_deleteOutgoingLink(struct Node * this)
{
	if ( 0 == (*this->outgoingLinkCount) ) {
		exit(1);
	}
	
	(*this->outgoingLinkCount) = (*this->outgoingLinkCount) - 1;
	
	if ( 0 == (*this->outgoingLinkCount) ) {
		(*this->outgoingLink) = 0;
	}
}

void Node_deleteIncomingLink(struct Node * this)
{
	if ( 0 == (*this->incomingLinkCount) ) {
		exit(1);
	}
	
	(*this->incomingLinkCount) = (*this->incomingLinkCount) - 1;
	
	if ( 0 == (*this->incomingLinkCount) ) {
		(*this->incomingLink) = 0;
	}
}