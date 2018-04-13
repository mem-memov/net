#include "Node.h"
#include <stdlib.h>
#include "Link.h"

#include <stdio.h>

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
	
	if ( ! Node_isNode(this) ) {
		exit(1);
	}
}

size_t Node_getPlace(struct Node * this)
{
	return (*this->place);
}

char Node_isNode(struct Node * this)
{
	if ( this->places[(*this->place)] == (*this->place) ) {
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
		Link_moveBackwardsInIncoming(this->link, Link_getPlace(link));
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
		Link_moveBackwardsInOutgoing(this->link, Link_getPlace(link));
	}
	
	(*this->outgoingLink) = Link_getPlace(link);
	(*this->outgoingLinkCount) += 1;
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
	} while( ! Link_isLastOutgoing(this->link));
	
	return 0;
}