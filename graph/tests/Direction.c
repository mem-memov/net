#include "../source/Direction.h"
#include <stdlib.h>
#include "../source/DirectionError.h"

struct Direction {
	size_t place;
	size_t destination;
	size_t previous;
	size_t next;
	size_t node;
	size_t result;
	char * method;
};

struct Direction * Direction_mock()
{
	struct Direction * this = malloc(sizeof(struct Direction));
	
	this->place = 55555;
	this->destination = 55555;
	this->previous = 55555;
	this->next = 55555;
	this->node = 55555;
	this->result = 55555;
	this->method = "method never called";

	return this;
}

void Direction_setPool(struct Direction * this, struct Direction * nextDirection)
{
	free(this);
	this = NULL;
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
	this->node = node;
	this->method = "Direction_hasNode";
	return this->result;
}

size_t Direction_getNode(struct Direction * this)
{
	this->method = "Direction_getNode";
	return this->result;
}

size_t Direction_getNext(struct Direction * this)
{
	this->method = "Direction_getNext";
	return this->result;
}

void Direction_delete(struct Direction * this)
{
	this->method = "Direction_delete";
}

