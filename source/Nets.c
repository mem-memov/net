#include "Nets.h"
#include <stdlib.h>

struct Nets
{
	struct Places * places;
	struct Gaps * gaps;
};

struct Nets * Nets_construct(struct Places * places, struct Gaps * gaps)
{
	struct Nets * this = malloc(sizeof(struct Nets));
	
	this->places = places;
	this->gaps = gaps;
	
	return this;
}

void Nets_destruct(struct Nets * this)
{
	free(this);
	this = NULL;
}

struct Net * Nets_make(struct Nets * this, size_t spaceSize, size_t entrySize)
{
	return Net_construct(
		spaceSize, 
		entrySize, 
		Places_make(this->places), 
		this->gaps,
		Places_make(this->places),
		Places_make(this->places),
		Places_make(this->places),
		Places_make(this->places),
		Places_make(this->places),
		Places_make(this->places)
	);
}
