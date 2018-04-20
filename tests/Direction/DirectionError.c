#include "../../source/DirectionError.h"
#include <stdlib.h>

struct DirectionError {
	size_t * previous;
	size_t * next;
	char * method;
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
	this->method = "DirectionError_forbidZeroPlaceForPrevious";
	this->previous = previous;
}

void DirectionError_forbidZeroAndEqualtyForPreviousAndNext(struct DirectionError * this, size_t * previous, size_t * next)
{
	this->method = "DirectionError_forbidZeroAndEqualtyForPreviousAndNext";
	this->previous = previous;
	this->next = next;
}