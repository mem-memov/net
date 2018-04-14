#include "Incoming.h"
#include <stdlib.h>

struct Incoming * Incoming_construct(size_t * places)
{
	struct Incoming * this = malloc(sizeof(struct Incoming));

	this->places = places;
	
	return this;
}

void Incoming_destruct(struct Incoming * this)
{
	free(this);
}

size_t Incoming_getPlace(struct Incoming * this)
{
	return this->place;
}

void Incoming_bind(struct Incoming * this, size_t place)
{
	this->place = place;
	
    this->node = this->places + place + 3;
    this->previous = this->places + place + 4;
    this->next = this->places + place + 5;
}

void Incoming_create(struct Incoming * this, size_t place, size_t origin)
{
	Incoming_bind(this, place);
	
	(*this->node) = origin;
	(*this->previous) = 0;
	(*this->next) = 0;
}

void Incoming_read(struct Incoming * this, size_t place)
{
	Incoming_bind(this, place);
}

void Incoming_joinChain(struct Incoming * this, size_t previous, size_t next)
{
	(*this->previous) = previous;
	(*this->next) = next;
}

void Incoming_append(struct Incoming * this, size_t previous)
{
	(*this->previous) = previous;
}

char Incoming_hasNode(struct Incoming * this, size_t node)
{
	if ( (*this->node) == node) {
		return 1;
	}
	
	return 0;
}

size_t Incoming_getNode(struct Incoming * this)
{
	return (*this->node);
}

size_t Incoming_getNext(struct Incoming * this)
{
	return (*this->next);
}

