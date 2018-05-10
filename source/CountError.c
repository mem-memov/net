#include "CountError.h"
#include <stdlib.h>

struct CountError
{
	//
};

struct CountError * CountError_construct()
{
	struct CountError * this = malloc(sizeof(struct CountError));

	return this;
}

void CountError_destruct(struct CountError * this)
{
	free(this);
	this = NULL;
}

void CountError_forbidNegativeValueWhenDecrementing(struct CountError * this, size_t value)
{
	if ( 0 == value) {
		exit(1);
	}
}

