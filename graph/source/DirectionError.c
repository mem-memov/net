#include "DirectionError.h"
#include <stdlib.h>
#include "Error.h"

struct DirectionError
{
	struct Error * error;
};

struct DirectionError * DirectionError_construct(struct Error * error)
{
	struct DirectionError * this = malloc(sizeof(struct DirectionError));
	
	this->error = error;

	return this;
}

void DirectionError_destruct(struct DirectionError * this)
{
	free(this);
	this = NULL;
}

void DirectionError_forbidZeroPlaceForPrevious(struct DirectionError * this, size_t previous)
{
	if ( 0 == previous ) {
		Error_terminate(this->error);
	}
}

void DirectionError_forbidZeroAndEqualtyForPreviousAndNext(struct DirectionError * this, size_t * previous, size_t * next)
{
	if ( 0 == previous || 0 == next || previous == next ) {
		Error_terminate(this->error);
	}
}