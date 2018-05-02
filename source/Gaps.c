#include "Gaps.h"
#include <stdlib.h>
#include "Gap.h"
#include "GapError.h"

struct Gaps
{
	struct Gap * gap;
	
	// pool
	struct GapError * gapError;
};

struct Gaps * Gaps_construct(struct GapError * gapError)
{
	struct Gaps * this = malloc(sizeof(struct Gaps));

	this->gap = NULL;
	
	this->gapError = gapError;
	
	return this;
}

void Gaps_destruct(struct Gaps * this)
{
	if (NULL != this->gap) {
		Gap_destruct(this->gap);
	}
	
	free(this);
	this = NULL;
}

void Gaps_addGap(struct Gaps * this, size_t place)
{
	if (NULL == this->gap) {
		this->gap = Gap_construct(place, NULL, this->gapError);
	} else {
		this->gap = Gap_construct(place, this->gap, this->gapError);
	}
}

char Gaps_areEmpty(struct Gaps * this)
{
	if ( NULL == this->gap ) {
		return 1;
	}
	
	return 0;
}

size_t Gaps_givePlace(struct Gaps * this)
{
	size_t place = Gap_getPlace(this->gap);
	this->gap = Gap_getNext(this->gap);
	
	return place;
}