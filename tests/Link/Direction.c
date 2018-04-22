#include "../../source/Direction.h"
#include <stdlib.h>
#include "../../source/DirectionError.h"

struct Direction {
	size_t place;
	size_t destination;
	size_t previous;
	size_t next;
	char * method;
};

struct Direction * Direction_construct(size_t * places, char offset, struct DirectionError * error)
{
	struct Direction * this = malloc(sizeof(struct Direction));

	return this;
}

struct Direction * Direction_constructOutgoing(size_t * places, struct DirectionError * error)
{
	return Direction_construct(places, 0, error);
}

struct Direction * Direction_constructIncoming(size_t * places, struct DirectionError * error)
{
	return Direction_construct(places, 3, error);
}

void Direction_setPool(struct Direction * this, struct Direction * nextDirection)
{

}

void Direction_destruct(struct Direction * this)
{

}

size_t Direction_getPlace(struct Direction * this)
{
	return 1;
}

void Direction_bind(struct Direction * this, size_t place)
{

}

void Direction_create(struct Direction * this, size_t place, size_t destination)
{
	this->place = place;
	this->destination = destination;
	this->method = "Direction_create";
}

void Direction_read(struct Direction * this, size_t place)
{
	this->place = place;
	this->method = "Direction_read";
}

void Direction_joinChain(struct Direction * this, size_t previous, size_t next)
{
	this->previous = previous;
	this->next = next;
	this->method = "Direction_joinChain";
}

void Direction_append(struct Direction * this, size_t previous)
{
	this->previous = previous;
	this->method = "Direction_append";
}

char Direction_hasNode(struct Direction * this, size_t node)
{
	return 0;
}

size_t Direction_getNode(struct Direction * this)
{
	return 1;
}

size_t Direction_getNext(struct Direction * this)
{
	return 1;
}

void Direction_delete(struct Direction * this)
{

}

