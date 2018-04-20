#include "GapError.h"
#include <stdlib.h>
#include <assert.h>

struct GapError {

};

struct GapError * GapError_construct()
{
	struct GapError * this = malloc(sizeof(struct GapError));

	return this;
}

void GapError_destruct(struct GapError * this)
{
	free(this);
	this = NULL;
}

void GapError_zeroPlaceIsReservedForInvalidGap(struct GapError * this, size_t place)
{
	assert(0 != place);
}

void GapError_placeCanBeReadOnlyOnce(struct GapError * this, size_t place)
{
	assert(0 != place);
}

