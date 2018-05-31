#include "NetError.h"
#include <stdlib.h>

struct NetError
{
	//
};

struct NetError * NetError_construct()
{
	struct NetError * this = malloc(sizeof(struct NetError));

	return this;
}

void NetError_destruct(struct NetError * this)
{
	free(this);
	this = NULL;
}