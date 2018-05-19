#include "Error.h"
#include <stdlib.h>

struct Error
{
	
};

struct Error * Error_construct()
{
	struct Error * this = malloc(sizeof(struct Error));
	
	return this;
}

void Error_destruct(struct Error * this)
{
	free(this);
	this = NULL;
}

void Error_terminate(struct Error * this)
{
	exit(1);
}