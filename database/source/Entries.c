#include "Entries.h"
#include <stdlib.h>

struct Entries
{
	//
};

struct Entries * Entries_construct()
{
	struct Entries * this = malloc(sizeof(struct Entries));

	return this;
}

void Entries_destruct(struct Entries * this)
{
	free(this);
	this = NULL;
}

struct Entry * Entries_make(struct Entries * this)
{
	return Entry_construct();
}