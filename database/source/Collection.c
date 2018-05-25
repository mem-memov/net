#include "Collection.h"
#include <stdlib.h>

struct Collection
{
	struct Entry ** entries;
	size_t length;
	char isFull;
	size_t index;
};

struct Collection * Collection_construct(size_t length)
{
	struct Collection * this = malloc(sizeof(struct Collection));
	
	this->entries = malloc(sizeof(struct Entry) * length);
	this->length = length;
	this->isFull = 0;
	this->index = 0;
	
	size_t index;
	for ( index = 0; index < length; index++ ) {
		this->entries[index] = NULL;
	}

	return this;
}

void Collection_destruct(struct Collection * this)
{
	free(this->entries);
	free(this);
	this = NULL;
}

void Collection_addEntry(struct Collection * this, struct Entry * entry)
{
	if (this->isFull) {
		exit(1);
	}
	
	this->entries[this->index] = entry;
	
	if ( this->index == this->length ) {
		this->isFull = 1;
	}
	
	this->index++;
}