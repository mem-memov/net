#include "Entry.h"
#include <stdlib.h>

struct Entry
{
	//
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

void Entry_read(struct Entry * this, size_t place)
{
	this->place = place;
}

char Entry_isEmpty(struct Entry * this)
{
	if (0 == this->place) {
		exit(1);
	}
	
	char position;
	
	for (position = 0; position < this->size; position++ ) {
		if (0 != this->places[this->place + position]) {
			return 0;
		}
	}
	
	return 1;
}
