#include "GapError.h"
#include <stdlib.h>
#include "Error.h"

struct GapError {
	struct Error * error;
};

struct GapError * GapError_construct(struct Error * error)
{
	struct GapError * this = malloc(sizeof(struct GapError));
	
	this->error = error;

	return this;
}

void GapError_destruct(struct GapError * this)
{
	free(this);
	this = NULL;
}

void GapError_zeroPlaceIsReservedForInvalidGap(struct GapError * this, size_t place)
{
	if (0 == place) {
		Error_terminate(this->error);
	}
}

void GapError_placeCanBeReadOnlyOnce(struct GapError * this, size_t place)
{
	if (0 == place) {
		Error_terminate(this->error);
	}
}

