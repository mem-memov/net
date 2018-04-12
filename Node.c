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
	this->outCount = this->places[place] + 2;
	this->inCount = this->places[place] + 3;
	this->outLink = this->places[place] + 4;
	this->inLink = this->places[place] + 5;	
}

void Node_create(struct Node * this, size_t place)
{
	Node_bind(this, place);

	(*this->place) = place;
	(*this->data) = 0;
	(*this->outCount) = 0;
	(*this->inCount) = 0;
	(*this->outLink) = 0;
	(*this->inLink) = 0;
}

void Node_read(struct Node * this, size_t place)
{
	Node_bind(this, place);
}

size_t Node_getPlace(struct Node * this)
{
	return (*this->place);
}

char Node_isNode(struct Node * this)
{
	if (this->places[(*this->place)] == (*this->place)) {
		return 1;
	}
	
	return 0;
}

char Node_isSame(struct Node * this, struct Node * that)
{
	if (* this->place == Node_getPlace(that)) {
		return 1;
	}
	
	return 0;
}

char Node_hasInLink(struct Node * this)
{
	if (* this->inLink != 0) {
		return 1;
	}
	
	return 0;
}

void Node_addInLink(struct Node * this, struct Link * link)
{
	if ( ! Node_hasInLink(this)) {
		* this->inLink = Link_getPlace(link);
		* this->inLinkCount = 1;
	} else {
		
	}
	

}

void Node_setOutLink(struct Node * this, struct Link * link)
{
	if (Node_hasOutLink(this)) {
		exit(1);
	}
	
	* this->outLink = Link_getPlace(link);
	* this->outLinkCount = 1;
}