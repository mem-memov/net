#include "../../source/Direction.h"
#include <stdlib.h>
#include "../../source/DirectionError.h"

struct Direction {

};

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

}

void Direction_read(struct Direction * this, size_t place)
{

}

void Direction_joinChain(struct Direction * this, size_t previous, size_t next)
{

}

void Direction_append(struct Direction * this, size_t previous)
{

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

