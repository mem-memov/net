#include "Direction.h"
#include <stdlib.h>

struct Direction {
	// type
	char offset;
	
	struct DirectionError * error;

	// pool
	struct Direction * nextDirection;
	
	// identifier
	size_t place;

	// fields
	struct Place * node;
	struct Place * previous;
	struct Place * next;
};

struct Direction * Direction_construct(
	char offset, 
	struct DirectionError * error,
	struct Place * node,
	struct Place * previous,
	struct Place * next
) {
	struct Direction * this = malloc(sizeof(struct Direction));
	
	this->offset = offset;
	
	this->error = error;
	
	this->node = node;
	this->previous = previous;
	this->next = next;

	this->nextDirection = NULL;

	return this;
}

struct Direction * Direction_constructOutgoing(	
	struct DirectionError * error,
	struct Place * node,
	struct Place * previous,
	struct Place * next
) {
	return Direction_construct(0, error, node, previous, next);
}

struct Direction * Direction_constructIncoming(
	struct DirectionError * error,
	struct Place * node,
	struct Place * previous,
	struct Place * next
) {
	return Direction_construct(3, error, node, previous, next);
}

void Direction_setPool(struct Direction * this, struct Direction * nextDirection)
{
	this->nextDirection = nextDirection;
}

void Direction_destruct(struct Direction * this)
{
	Place_destruct(this->node);
	Place_destruct(this->previous);
	Place_destruct(this->next);
	
	if (NULL != this->nextDirection) {
		Direction_destruct(this->nextDirection);
	}
	
	free(this);
	this = NULL;
}

size_t Direction_getPlace(struct Direction * this)
{
	return this->place;
}

void Direction_bind(struct Direction * this, size_t place)
{
	this->place = place;
	
	Place_bind(this->node, place + this->offset + 0);
	Place_bind(this->previous, place + this->offset + 1);
	Place_bind(this->next, place + this->offset + 2);
}

void Direction_create(struct Direction * this, size_t place, size_t destination)
{
	Direction_bind(this, place);
	
	Place_set(this->node, destination);
	Place_set(this->previous, 0);
	Place_set(this->next, 0);
}

void Direction_read(struct Direction * this, size_t place)
{
	Direction_bind(this, place);
}

void Direction_joinChain(struct Direction * this, size_t previous, size_t next)
{
	DirectionError_forbidZeroAndEqualtyForPreviousAndNext(this->error, & previous, & next);
	
	Place_set(this->previous, previous); // a node entry
	Place_set(this->next, next); // direction that pointed to the node before
}

void Direction_append(struct Direction * this, size_t previous)
{
	DirectionError_forbidZeroPlaceForPrevious(this->error, previous);
	
	Place_set(this->previous, previous);
}

char Direction_hasNode(struct Direction * this, size_t node)
{
	if ( Place_get(this->node) == node) {
		return 1;
	}
	
	return 0;
}

size_t Direction_getNode(struct Direction * this)
{
	return Place_get(this->node);
}

size_t Direction_getNext(struct Direction * this)
{
	return Place_get(this->next);
}

void Direction_delete(struct Direction * this)
{
	DirectionError_forbidZeroPlaceForPrevious(this->error, Place_get(this->previous));
	
	if ( ! Place_isZero(this->next) ) {
		Direction_read(this->nextDirection, Place_get(this->next));
		Direction_append(this->nextDirection, Place_get(this->previous));
	}

	Place_set(this->node, 0);
	Place_set(this->previous, 0);
	Place_set(this->next, 0);
}

