#include "DirectionError.h"
#include <stdlib.h>

struct DirectionError {

};

struct DirectionError * DirectionError_construct()
{
	struct DirectionError * this = malloc(sizeof(struct DirectionError));

	return this;
}

void DirectionError_destruct(struct DirectionError * this)
{
	free(this);
	this = NULL;
}

void DirectionError_forbidZeroPlaceForPrevious(struct DirectionError * this, size_t * previous)
{
	if ( 0 == (*previous) ) {
		exit(1);
	}
}

void DirectionError_forbidZeroAndEqualtyForPreviousAndNext(struct DirectionError * this, size_t * previous, size_t * next)
{
	if ( 0 == (*previous) || 0 == (*next) || (*previous) == (*next) ) {
		exit(1);
	}
}