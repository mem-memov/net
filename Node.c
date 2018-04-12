#include "Node.h"
#include <stdlib.h>
#include "Link.h"

struct Node * Node_construct(size_t * places)
{
	struct Node * this = malloc(sizeof(struct Node));

	this->places = places;

	return this;
}

void Node_destruct(struct Node * this)
{
	free(this);
}

void Node_bind(struct Node * this, size_t place)
{
	this->place = this->places[place] + 0;
	this->data = this->places[place] + 1;
	this->outgoingLinkCount = this->places[place] + 2;
	this->incomingLinkCount = this->places[place] + 3;
	this->outgoingLink = this->places[place] + 4;
	this->incomingLink = this->places[place] + 5;	
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
	
	if ( ! Node_isNode(this) )
	{
		exit(1);
	}
}

size_t Node_getPlace(struct Node * this)
{
	return (*this->place);
}

char Node_isNode(struct Node * this)
{
	if ( this->places[(*this->place)] == (*this->place) )
	{
		return 1;
	}
	
	return 0;
}

char Node_isSame(struct Node * this, struct Node * that)
{
	if ( (*this->place) == Node_getPlace(that) )
	{
		return 1;
	}
	
	return 0;
}

char Node_hasIncomingLink(struct Node * this)
{
	if ( (*this->incomingLink) != 0 )
	{
		return 1;
	}
	
	return 0;
}


char Node_hasOutgoingLink(struct Node * this)
{
	if ( (*this->outgoingLink) != 0 )
	{
		return 1;
	}
	
	return 0;
}

void Node_addIncomingLink(struct Node * this, struct Link * link)
{
	if ( ! Node_hasIncomingLink(this))
	{
		Link_joinIncomingChain(link, (*this->place), 0);

	} else {
		
		Link_joinIncomingChain(link, (*this->place), (*this->incomingLink));
	}
	
	(*this->incomingLink) = Link_getPlace(link);
	(*this->incomingLinkCount) += 1;
}

void Node_addOutgoingLink(struct Node * this, struct Link * link)
{
	if (Node_hasOutgoingLink(this))
	{
		exit(1);
	}
	
	(*this->outgoingLink) = Link_getPlace(link);
	(*this->outgoingLinkCount) = 1;
}