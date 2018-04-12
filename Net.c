#include "Net.h"
#include <stdlib.h>

struct Net * Net_construct(size_t * places, size_t spaceSize, size_t entrySize, size_t placeSize)
{
	struct Net * this = malloc(sizeof(struct Net));

	this->places = places;
	this->spaceSize = spaceSize;
	this->entrySize = entrySize;
	this->placeSize = placeSize;

	return this;
}

void Net_destruct(struct Net * this)
{
	free(this);
}

void Net_create(struct Net * this)
{
	this->one = 1;
	this->places[0] = this->one;
	
	this->data = 0;
	this->places[1] = this->data;

	this->places[2] = this->placeSize;
	
	this->nextPlace = 1;
	this->places[3] = this->nextPlace;
	
	this->nodeCount = 0;
	this->places[4] = this->nodeCount;
	
	this->linkCount = 0;
	this->places[5] = this->linkCount;
}

char Net_hasSpaceForEntry(struct Net * this)
{
	if (this->nextPlace < this->spaceSize) {
		return 1;
	}
	
	return 0;
}

size_t Net_createEntry(struct Net * this, struct Gap * gap)
{
	if ( ! Net_hasSpaceForEntry(this)) {
		exit(1);
	}
	
	size_t place;

	if (NULL != gap) {
		place = Gap_getPlace(gap);
		gap = Gap_getNext(gap);
	} else {
		place = this->nextPlace * this->entrySize;
	}
	
	this->nextPlace += this->entrySize;
	
	this->places[3] = this->nextPlace;
	
	return place;
}

void Net_incrementNodes(struct Net * this, size_t * places)
{
	this->places[4] += 1;
}

void Net_decrementNodes(struct Net * this, size_t * places)
{
	this->places[4] -= 1;
}

void Net_incrementLinks(struct Net * this, size_t * places)
{
	this->places[5] += 1;
}

void Net_decrementLinks(struct Net * this, size_t * places)
{
	this->places[5] -= 1;
}

