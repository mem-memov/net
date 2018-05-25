#include "Collection.h"
#include <stdlib.h>

struct Collection
{
	struct Entry ** entries;
	size_t length;
};

struct Collection * Collection_construct(struct Entry ** entries, size_t length)
{
	struct Collection * this = malloc(sizeof(struct Collection));
	
	this->entries = entries;
	this->length = length;

	return this;
}

void Collection_destruct(struct Collection * this)
{
	free(this);
	this = NULL;
}

