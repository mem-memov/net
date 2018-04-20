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
}
