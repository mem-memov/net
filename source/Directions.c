#include "Directions.h"
#include <stdlib.h>

struct Directions
{
	struct Places * places;
	struct DirectionError * directionError;
};

struct Directions * Directions_construct(struct Places * places, struct DirectionError * directionError)
{
	struct Directions * this = malloc(sizeof(struct Directions));
	
	this->places = places;
	this->directionError = directionError;
	
	return this;
}

void Directions_destruct(struct Directions * this)
{
	free(this);
	this = NULL;
}

struct Direction * Directions_makeOutgoing(struct Directions * this)
{
	return Direction_constructOutgoing(
		this->directionError,
		Places_make(this->places),
		Places_make(this->places),
		Places_make(this->places)
	);
}

struct Direction * Directions_makeIncoming(struct Directions * this)
{
	return Direction_constructIncoming(
		this->directionError,
		Places_make(this->places),
		Places_make(this->places),
		Places_make(this->places)
	);
}