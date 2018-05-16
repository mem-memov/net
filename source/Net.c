#include "Net.h"

struct Net {
	size_t spaceSize;
	size_t entrySize;
	
	struct Mesh * mesh;
	
	struct Exports * exports;
	
	struct Place * one;
	struct Place * placeSize;
	struct Place * nextPlace;
	struct Place * gapPlace;
	struct Count * nodeCount;
	struct Count * linkCount;
};

struct Net * Net_construct(
	size_t spaceSize, 
	size_t entrySize, 
	struct Mesh * mesh,
	struct Exports * exports,
	struct Place * one,
	struct Place * placeSize,
	struct Place * nextPlace,
	struct Place * gapPlace,
	struct Count * nodeCount,
	struct Count * linkCount
) {
	struct Net * this = malloc(sizeof(struct Net));

	this->spaceSize = spaceSize;
	this->entrySize = entrySize;

	this->mesh = mesh;
	
	this->exports = exports;
	
	// fields
	this->one = one;
	this->placeSize = placeSize;
	this->nextPlace = nextPlace;
	this->gapPlace = gapPlace;
	this->nodeCount = nodeCount;
	this->linkCount = linkCount;

	return this;
}

void Net_destruct(struct Net * this)
{
	Mesh_destruct(this->mesh);
	
	Place_destruct(this->one);
	Place_destruct(this->placeSize);
	Place_destruct(this->nextPlace);
	Place_destruct(this->gapPlace);
	Count_destruct(this->nodeCount);
	Count_destruct(this->linkCount);
	
	free(this);
	this = NULL;
}

void Net_create(struct Net * this, size_t placeSize)
{
	Net_read(this);
	
	Place_set(this->one, 1);
	Place_set(this->placeSize, placeSize);
	Place_set(this->nextPlace, this->entrySize);
	Place_set(this->gapPlace, 0);
	Count_create(this->nodeCount);
	Count_create(this->linkCount);
}

void Net_read(struct Net * this)
{
	Place_bind(this->one, 0);
	Place_bind(this->placeSize, 1);
	Place_bind(this->nextPlace, 2);
	Place_bind(this->gapPlace, 3);
	Count_bind(this->nodeCount, 4);
	Count_bind(this->linkCount, 5);
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
	
	if ( 0 != Place_get(this->gapPlace) ) {
		return 1;
	}
	
	return 0;
}

size_t Net_createEntry(struct Net * this, char nodeNotLink)
{
	if ( ! Net_hasSpaceForEntry(this)) {
		exit(1);
	}
	
	size_t place = Place_get(this->gapPlace);
	
	size_t nextGapPlace;

	if ( 0 != place ) {
		nextGapPlace = Mesh_removeGap(this->mesh, place);
		Place_set(this->gapPlace, nextGapPlace);
	} else {
		place = Place_get(this->nextPlace);
		Place_set(this->nextPlace, Place_get(this->nextPlace) + this->entrySize);
	}
	
	switch ( nodeNotLink ) {
		case 0:
			Count_increment(this->linkCount);
			break;
		case 1:
			Count_increment(this->nodeCount);
			break;
		default:
			exit(1);
			break;
	}

	return place;
}

struct Export * Net_createExport(struct Net * this)
{
	size_t size = Place_get(this->placeSize) * Place_get(this->nextPlace);
	
	return Exports_make(this->exports, size);
}

void Net_import(struct Net * this, struct Stream * stream)
{
	if (Net_isSpaceCut(this)) { // TODO: move to error file
		exit(1);
	}
	
	size_t placeSize = Place_get(this->placeSize);
	size_t nextPlace = Place_get(this->nextPlace);

	size_t offset = this->entrySize * placeSize;
	size_t size = nextPlace * placeSize - offset;
	
	Stream_read(stream, offset, size);
}

void Net_addGap(struct Net * this, size_t place, char nodeNotLink)
{
	size_t nextGapPlace = Place_get(this->gapPlace);
	
	Mesh_addGap(this->mesh, place, nextGapPlace);
	
	Place_set(this->gapPlace, place);
	
	switch ( nodeNotLink ) {
		case 0:
			Count_decrement(this->linkCount);
			break;
		case 1:
			Count_decrement(this->nodeCount);
			break;
		default:
			exit(1);
			break;
	}
}