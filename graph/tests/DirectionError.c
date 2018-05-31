#include "../source/DirectionError.h"
#include <stdlib.h>

#define DIRECTIONERROR_MAX_CALLS 1

struct DirectionError {
	char call;
	char * method[DIRECTIONERROR_MAX_CALLS];
	size_t previous[DIRECTIONERROR_MAX_CALLS];
	size_t next[DIRECTIONERROR_MAX_CALLS];
};

struct DirectionError * DirectionError_mock()
{
	struct DirectionError * this = malloc(sizeof(struct DirectionError));

	this->call = 0;
	
	char i;
	for (i = 0; i < DIRECTIONERROR_MAX_CALLS; i++) {
		this->method[i] = "method never called";
		this->previous[i] = 5555;
		this->next[i] = 5555;
	}
	
	return this;
}

void DirectionError_destruct(struct DirectionError * this)
{
	free(this);
	this = NULL;
}

void DirectionError_forbidZeroPlaceForPrevious(struct DirectionError * this, size_t previous)
{
	this->method[this->call] = "DirectionError_forbidZeroPlaceForPrevious";
	this->previous[this->call] = previous;
	
	this->call++;
}

void DirectionError_forbidZeroAndEqualtyForPreviousAndNext(struct DirectionError * this, size_t * previous, size_t * next)
{
	this->method[this->call] = "DirectionError_forbidZeroAndEqualtyForPreviousAndNext";
	this->previous[this->call] = (*previous);
	this->next[this->call] = (*next);
	
	this->call++;
}