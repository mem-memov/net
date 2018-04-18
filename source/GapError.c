#include "GapError.h"
#include <stdlib.h>

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
}

void GapError_zeroPlaceIsReservedForInvalidGap(struct GapError * this, size_t place)
{
	if (0 == place) {
		exit(1);
	}
}

void GapError_placeCanBeReadOnlyOnce(struct GapError * this, size_t place)
{
	if (0 == place) {
		exit(1);
	}
}

