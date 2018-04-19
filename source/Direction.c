#include "Direction.h"
#include <stdlib.h>

struct Direction {
	// store
	size_t * places;
	
	// type
	char offset;

	// pool
	struct Direction * nextDirection;
	
	// identifier
	size_t place;

	// fields
	size_t * node;
	size_t * previous;
	size_t * next;
};

struct Direction * Direction_construct(size_t * places, char offset)
{
	struct Direction * this = malloc(sizeof(struct Direction));

	this->places = places;
	
	this->offset = offset;

	this->nextDirection = NULL;

	return this;
}

struct Direction * Direction_constructOutgoing(size_t * places)
{
	return Direction_construct(places, 0);
}

struct Direction * Direction_constructIncoming(size_t * places)
{
	return Direction_construct(places, 3);
}

void Direction_setPool(struct Direction * this, struct Direction * nextDirection)
{
	this->nextDirection = nextDirection;
}

void Direction_destruct(struct Direction * this)
{
	free(this);
}

size_t Direction_getPlace(struct Direction * this)
{
	return this->place;
}

void Direction_bind(struct Direction * this, size_t place)
{
	this->place = place;
    this->node = this->places + place + this->offset + 0;
    this->previous = this->places + place + this->offset + 1;
    this->next = this->places + place + this->offset + 2;
}

void Direction_create(struct Direction * this, size_t place, size_t destination)
{
	Direction_bind(this, place);
	
	(*this->node) = destination;
	(*this->previous) = 0;
	(*this->next) = 0;
}

void Direction_read(struct Direction * this, size_t place)
{
	Direction_bind(this, place);
}

void Direction_joinChain(struct Direction * this, size_t previous, size_t next)
{
	(*this->previous) = previous;
	(*this->next) = next;
}

void Direction_append(struct Direction * this, size_t previous)
{
	(*this->previous) = previous;
}

char Direction_hasNode(struct Direction * this, size_t node)
{
	if ( (*this->node) == node) {
		return 1;
	}
	
	return 0;
}

size_t Direction_getNode(struct Direction * this)
{
	return (*this->node);
}

size_t Direction_getNext(struct Direction * this)
{
	return (*this->next);
}

void Direction_delete(struct Direction * this)
{
	Direction_read(this->nextDirection, (*this->next));
	Direction_append(this->nextDirection, (*this->previous));
	
	(*this->node) = 0;
	(*this->previous) = 0;
	(*this->next) = 0;
}
