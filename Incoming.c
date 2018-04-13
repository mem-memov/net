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

void Incoming_bind(struct Incoming * this, size_t place)
{
	this->place = place;
	
    this->node = this->places + place + 0;
    this->previous = this->places + place + 1;
    this->next = this->places + place + 2;
}

void Incoming_create(struct Incoming * this, size_t place, size_t origin)
{
	Incoming_bind(this, place);
	
	(*this->node) = origin;
	(*this->previous) = 0;
	(*this->next) = 0;
}

