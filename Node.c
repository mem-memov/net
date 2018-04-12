#include "Node.h"
#include <stdlib.h>

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

void Node_create(struct Node * this, size_t place)
{
	this->place = place;
	this->places[place][0] = this->place;
	
	this->data = 0;
	this->places[place][1];
	
	this->outCount = 0;
	this->places[place][2] = this->outCount;
	
	this->inCount = 0;
	this->places[place][3] = this->inCount;
	
	this->outLink = 0;
	this->places[place][4] = this->outLink;
	
	this->inLink = 0;
	this->places[place][5] = this->inLink;
}

void Node_read(struct Node * this, size_t place)
{
	this->place = place;
	this->data = this->places[place][1];
	this->outCount = this->places[place][2];
	this->inCount = this->places[place][3];
	this->outLink = this->places[place][4];
	this->inLink = this->places[place][5];
}

size_t Node_getPlace(struct Node * this)
{
	return this->place;
}

char Node_isSame(struct Node * this, struct Node * that)
{
	if (Node_getPlace(this) == Node_getPlace(that)) {
		return 1;
	}
	
	return 0;
}

