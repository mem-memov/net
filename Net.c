#include "Net.h"
#include <stdlib.h>
#include <stdio.h>
#include "Gap.h"


struct Net * Net_construct(size_t * places, size_t spaceSize, size_t entrySize)
{
	struct Net * this = malloc(sizeof(struct Net));

	this->places = places;
	this->spaceSize = spaceSize;
	this->entrySize = entrySize;

	return this;
}

void Net_destruct(struct Net * this)
{
	free(this);
}

void Net_bind(struct Net * this)
{
	this->one = this->places + 0;
	this->data = this->places + 1;
	this->placeSize = this->places + 2;
	this->nextPlace = this->places + 3;
	this->nodeCount = this->places + 4;
	this->linkCount = this->places + 5;	
}

void Net_create(struct Net * this, size_t placeSize)
{
	Net_bind(this);
	
	(*this->one) = 1;
	(*this->data) = 0;
	(*this->placeSize) = placeSize;
	(*this->nextPlace) = this->entrySize;
	(*this->nodeCount) = 0;
	(*this->linkCount) = 0;
}

char Net_isSpaceCut(struct Net * this)
{
	if ( (*this->nextPlace) > this->spaceSize ) {
		return 1;
	}
	
	return 0;
}

char Net_hasSpaceForEntry(struct Net * this)
{
	if ( (*this->nextPlace) < this->spaceSize ) {
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
		place = (*this->nextPlace);
	}

	(*this->nextPlace) += this->entrySize;
	
	return place;
}

void Net_incrementNodes(struct Net * this)
{
	(*this->nodeCount) += 1;
}

void Net_decrementNodes(struct Net * this)
{
	(*this->nodeCount) -= 1;
}

void Net_incrementLinks(struct Net * this)
{
	(*this->linkCount) += 1;
}

void Net_decrementLinks(struct Net * this)
{
	(*this->linkCount) -= 1;
}

void Net_export(struct Net * this, FILE * file)
{
	size_t placeCount = fwrite(this->places, (*this->placeSize), (*this->nextPlace), file);
	
	if ( placeCount != (*this->nextPlace) ) {
		exit(1);
	}
}

void Net_import(struct Net * this, FILE * file)
{
	size_t placeCount = fread(this->places + this->entrySize, (*this->placeSize), (*this->nextPlace) - 1, file);

	if ( placeCount != (*this->nextPlace) - 1 ) {
		exit(1);
	}
}
