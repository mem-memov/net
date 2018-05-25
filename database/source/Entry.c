#include "Entry.h"
#include <stdlib.h>

struct Entry
{
	size_t identifier;
};

struct Entry * Entry_construct()
{
	struct Entry * this = malloc(sizeof(struct Entry));

	return this;
}

void Entry_destruct(struct Entry * this)
{
	free(this);
	this = NULL;
}

