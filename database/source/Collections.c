#include "Collections.h"
#include <stdlib.h>

struct Collections
{
	//
};

struct Collections * Collections_construct()
{
	struct Collections * this = malloc(sizeof(struct Collections));

	return this;
}

void Collections_destruct(struct Collections * this)
{
	free(this);
	this = NULL;
}

struct Collection * Collections_make(struct Collections * this, size_t length)
{
	return Collection_construct(size_t length);
}