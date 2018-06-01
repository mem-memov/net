#include "Spaces.h"
#include <stdlib.h>

struct Spaces
{
	//
};

struct Spaces * Spaces_construct()
{
	struct Spaces * this = malloc(sizeof(struct Spaces));

	return this;
}

void Spaces_destruct(struct Spaces * this)
{
	free(this);
	this = NULL;
}

struct Space * Spaces_make(struct Spaces * this)
{
	return Space_construct();
}