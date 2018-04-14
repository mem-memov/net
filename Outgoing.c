#include "Outgoing.h"
#include <stdlib.h>

struct Outgoing * Outgoing_construct(size_t * places)
{
	struct Outgoing * this = malloc(sizeof(struct Outgoing));
	
	this->places = places;

	return this;
}

void Outgoing_destruct(struct Outgoing * this)
{
	free(this);
}

size_t Outgoing_getPlace(struct Outgoing * this)
{
	return this->place;
}

void Outgoing_bind(struct Outgoing * this, size_t place)
{
	this->place = place;
	
    this->node = this->places + place + 0;
    this->previous = this->places + place + 1;
    this->next = this->places + place + 2;
}

void Outgoing_create(struct Outgoing * this, size_t place, size_t destination)
{
	Outgoing_bind(this, place);
	
	(*this->node) = destination;
	(*this->previous) = 0;
	(*this->next) = 0;
}

void Outgoing_read(struct Outgoing * this, size_t place)
{
	Outgoing_bind(this, place);
}

void Outgoing_joinChain(struct Outgoing * this, size_t previous, size_t next)
{
	(*this->previous) = previous;
	(*this->next) = next;
}

void Outgoing_append(struct Outgoing * this, size_t previous)
{
	(*this->previous) = previous;
}

char Outgoing_hasNode(struct Outgoing * this, size_t node)
{
	if ( (*this->node) == node) {
		return 1;
	}
	
	return 0;
}

size_t Outgoing_getNext(struct Outgoing * this)
{
	return (*this->next);
}