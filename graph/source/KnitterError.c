#include "KnitterError.h"
#include <stdlib.h>

struct KnitterError
{
	//
};

struct KnitterError * KnitterError_construct()
{
	struct KnitterError * this = malloc(sizeof(struct KnitterError));

	return this;
}

void KnitterError_destruct(struct KnitterError * this)
{
	free(this);
	this = NULL;
}

void KnitterError_requireFittingInSize(struct KnitterError * this, size_t nextPlace, size_t graphSize)
{
	if ( nextPlace - 1 > graphSize ) {
		Error_terminate(this->error);
	}
}