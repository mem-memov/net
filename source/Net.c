#include "Net.h"
#include <stdlib.h>
#include <stdio.h>
#include "Gap.h"
#include "GapError.h"

struct Net {
	size_t * places;
	size_t spaceSize;
	size_t entrySize;
	struct Gap * gap;
	
	size_t * one;
	size_t * data;
	size_t * placeSize;
	size_t * nextPlace;
	size_t * nodeCount;
	size_t * linkCount;
};

struct Net * Net_construct(size_t * places, size_t spaceSize, size_t entrySize)
{
	struct Net * this = malloc(sizeof(struct Net));

	this->places = places;
	this->spaceSize = spaceSize;
	this->entrySize = entrySize;
	this->gap = NULL;

	return this;
}

void Net_destruct(struct Net * this)
{
	if (NULL != this->gap) {
		Gap_destruct(this->gap);
	}
	
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

void Net_read(struct Net * this)
{
	Net_bind(this);
}

char Net_isHead(struct Net * this, size_t place)
{
	if (place < this->entrySize) {
		return 1;
	}
	
	return 0;
}

char Net_isInside(struct Net * this, size_t place)
{
	if ( place < (*this->nextPlace) ) {
		return 1;
	}
	
	return 0;
}

char Net_isSpaceCut(struct Net * this)
{
	if ( (*this->nextPlace) - 1 > this->spaceSize ) {
		return 1;
	}
	
	return 0;
}

char Net_hasSpaceForEntry(struct Net * this)
{
	if ( (*this->nextPlace) < this->spaceSize && NULL == this->gap ) {
		return 1;
	}
	
	return 0;
}

size_t Net_createEntry(struct Net * this)
{
	if ( ! Net_hasSpaceForEntry(this)) {
		exit(1);
	}
	
	size_t place;

	if (NULL != this->gap) {
		place = Gap_getPlace(this->gap);
		this->gap = Gap_getNext(this->gap);
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
	size_t placeCount = fread(this->places + this->entrySize, (*this->placeSize), (*this->nextPlace), file);

	if ( placeCount != (*this->nextPlace) - this->entrySize ) {
		exit(1);
	}
	
	Net_scanForGaps(this);
}

void Net_scanForGaps(struct Net * this)
{
	size_t entryPlace;
	char entryPosition;
	char isEmpty;
	
	for ( entryPlace = this->entrySize; entryPlace < (*this->nextPlace); entryPlace++ ) {

		isEmpty = 1;
		for (entryPosition = 0; entryPosition < this->entrySize; entryPosition++ ) {
			if (this->places[entryPlace + entryPosition] != 0) {
				isEmpty = 0;
				break;
			}
		}

		if (! isEmpty) {
			break;
		}
		
		Net_addGap(this, entryPlace);
	}
}

void Net_addGap(struct Net * this, size_t place)
{
	struct GapError * error = GapError_construct();
	
	if (NULL == this->gap) {
		this->gap = Gap_construct(place, NULL, error);
	} else {
		this->gap = Gap_construct(place, this->gap, error);
	}
}