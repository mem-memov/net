#include "Net.h"
#include <stdlib.h>
#include <stdio.h>
#include "Entry.h"
#include "Gaps.h"
#include "Place.h"

struct Net {
	size_t spaceSize;
	size_t entrySize;
	struct Gaps * gaps;
	
	struct Place * one;
	struct Place * placeSize;
	struct Place * nextPlace;
	struct Place * gapCount;
	struct Place * nodeCount;
	struct Place * linkCount;
	
	struct Entry * entry;
};

struct Net * Net_construct(
	size_t spaceSize, 
	size_t entrySize, 
	struct Entry * entry, 
	struct Gaps * gaps,
	struct Place * one,
	struct Place * placeSize,
	struct Place * nextPlace,
	struct Place * gapCount,
	struct Place * nodeCount
) {
	struct Net * this = malloc(sizeof(struct Net));

	this->places = places;
	this->spaceSize = spaceSize;
	this->entrySize = entrySize;
	this->gaps = gaps;
	
	// pool
	this->entry = entry;
	
	// fields
	this->one = one;

	return this;
}

void Net_destruct(struct Net * this)
{
	Gaps_destruct(this->gaps);
	
	free(this);
	this = NULL;
}

void Net_bind(struct Net * this)
{
	this->one = this->places + 0;
	this->placeSize = this->places + 1;
	this->nextPlace = this->places + 2;
	this->gapCount = this->places + 3;
	this->nodeCount = this->places + 4;
	this->linkCount = this->places + 5;	
}

void Net_create(struct Net * this, size_t placeSize)
{
	Net_bind(this);
	
	(*this->one) = 1;
	(*this->placeSize) = placeSize;
	(*this->nextPlace) = this->entrySize;
	(*this->gapCount) = 0;
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
	if ( (*this->nextPlace) < this->spaceSize ) {
		return 1;
	}
	
	if ( ! Gaps_areEmpty(this->gaps) ) {
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

	if ( ! Gaps_areEmpty(this->gaps) ) {
		place = Gaps_givePlace(this->gaps);
		(*this->gapCount)--;
	} else {
		place = (*this->nextPlace);
		(*this->nextPlace) += this->entrySize;
	}

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
	if ( 0 == (*this->gapCount)) {
		return;
	}
	
	size_t count = 0;
	size_t place;
	
	for ( place = this->entrySize; place < (*this->nextPlace); place++ ) {
		
		Entry_read(this->entry, place);
		
		if ( Entry_isEmpty(this->entry) ) {
			Gaps_addGap(this->gaps, place);
			count++;
		}
		
		if ( count == (*this->gapCount) ) {
			return;
		}
	}
}

void Net_addGap(struct Net * this, size_t place)
{
	Gaps_addGap(this->gaps, place);
	(*this->gapCount)++;
}