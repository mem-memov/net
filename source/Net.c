#include "Net.h"
#include <stdlib.h>
#include <stdio.h>

struct Net {
	size_t spaceSize;
	size_t entrySize;
	
	struct Place * entry;
	
	struct Gaps * gaps;
	
	struct Exports * exports;
	
	struct Scan * scan;
	
	struct Place * one;
	struct Place * placeSize;
	struct Place * nextPlace;
	struct Count * gapCount;
	struct Count * nodeCount;
	struct Count * linkCount;
};

struct Net * Net_construct(
	size_t spaceSize, 
	size_t entrySize, 
	struct Place * entry, 
	struct Gaps * gaps,
	struct Exports * exports,
	struct Scan * scan,
	struct Place * one,
	struct Place * placeSize,
	struct Place * nextPlace,
	struct Count * gapCount,
	struct Count * nodeCount,
	struct Count * linkCount
) {
	struct Net * this = malloc(sizeof(struct Net));

	this->spaceSize = spaceSize;
	this->entrySize = entrySize;
	
	// pool
	this->entry = entry;
	
	this->gaps = gaps;
	
	this->exports = exports;
	
	// fields
	this->one = one;
	this->placeSize = placeSize;
	this->nextPlace = nextPlace;
	this->gapCount = gapCount;
	this->nodeCount = nodeCount;
	this->linkCount = linkCount;

	return this;
}

void Net_destruct(struct Net * this)
{
	Gaps_destruct(this->gaps);
	
	Place_destruct(this->one);
	Place_destruct(this->placeSize);
	Place_destruct(this->nextPlace);
	Count_destruct(this->gapCount);
	Count_destruct(this->nodeCount);
	Count_destruct(this->linkCount);
	
	free(this);
	this = NULL;
}

void Net_bind(struct Net * this)
{
	Place_bind(this->one, 0);
	Place_bind(this->placeSize, 1);
	Place_bind(this->nextPlace, 2);
	Count_bind(this->gapCount, 3);
	Count_bind(this->nodeCount, 4);
	Count_bind(this->linkCount, 5);
}

void Net_create(struct Net * this, size_t placeSize)
{
	Net_bind(this);
	
	Place_set(this->one, 1);
	Place_set(this->placeSize, placeSize);
	Place_set(this->nextPlace, this->entrySize);
	Count_create(this->gapCount);
	Count_create(this->nodeCount);
	Count_create(this->linkCount);
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
	if ( place < Place_get(this->nextPlace) ) {
		return 1;
	}
	
	return 0;
}

char Net_isSpaceCut(struct Net * this)
{
	if ( Place_get(this->nextPlace) - 1 > this->spaceSize ) {
		return 1;
	}
	
	return 0;
}

char Net_hasSpaceForEntry(struct Net * this)
{
	if ( Place_get(this->nextPlace) < this->spaceSize ) {
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
		Count_decrement(this->gapCount);
	} else {
		place = Place_get(this->nextPlace);
		Place_set(this->nextPlace, Place_get(this->nextPlace) + this->entrySize);
	}

	return place;
}

void Net_incrementNodes(struct Net * this)
{
	Count_increment(this->nodeCount);
}

void Net_decrementNodes(struct Net * this)
{
	Count_decrement(this->nodeCount);
}

void Net_incrementLinks(struct Net * this)
{
	Count_increment(this->linkCount);
}

void Net_decrementLinks(struct Net * this)
{
	Count_decrement(this->linkCount);
}

struct Export * Net_createExport(struct Net * this)
{
	size_t size = this->entrySize * Place_get(this->placeSize) * Place_get(this->nextPlace);
	
	return Exports_make(this->exports, size);
}

void Net_import(struct Net * this, unsigned char * bytes, FILE * file)
{
	size_t placeSize = Place_get(this->placeSize);
	size_t nextPlace = Place_get(this->nextPlace);
	
	size_t size = nextPlace * this->entrySize * placeSize;
	
	size_t byteCount = fread(bytes + this->entrySize, sizeof(unsigned char), size, file);

	if ( byteCount != nextPlace - this->entrySize) {
		exit(1);
	}
	
	size_t gapCount = Scan_findGaps(this->scan);
}

void Net_addGap(struct Net * this, size_t place)
{
	Gaps_addGap(this->gaps, place);
	Count_increment(this->gapCount);
}