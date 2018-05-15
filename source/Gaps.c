#include "Gaps.h"
#include <stdlib.h>

struct Gaps
{
	// factories
	struct Places * places;
	
	struct GapError * gapError;
};

struct Gaps * Gaps_construct(
	struct Places * places, 
	struct GapError * gapError
) {
	struct Gaps * this = malloc(sizeof(struct Gaps));

	// factories
	this->places = places;
	
	this->gapError = gapError;
	
	return this;
}

void Gaps_destruct(struct Gaps * this)
{
	free(this);
	this = NULL;
}

struct Gap * Gaps_make(struct Gaps * this)
{
	return Gap_construct(
		Places_make(this->places),
		Places_make(this->places),
		Places_make(this->places),
		Places_make(this->places),
		Places_make(this->places),
		Places_make(this->places),
		this->gapError
	);
}
