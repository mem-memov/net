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