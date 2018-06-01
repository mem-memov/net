#include "Net.h"

struct Net
{
	size_t entrySize;
	
	// fields
	struct Place * placeSize;
	struct Place * nextPlace;
	struct Place * gapPlace;
	
	struct Mesh * mesh;
	struct Space * space;
	
	struct NetError * error;
};

struct Net * Net_construct(
	size_t entrySize, 
	struct Place * placeSize,
	struct Place * nextPlace,
	struct Place * gapPlace,
	struct Mesh * mesh,
	struct Space * space,
	struct NetError * error
) {
	struct Net * this = malloc(sizeof(struct Net));
	
	this->entrySize = entrySize;
	
	// fields
	this->placeSize = placeSize;
	this->nextPlace = nextPlace;
	this->gapPlace = gapPlace;
	
	this->mesh = mesh;
	this->space = space;
	
	this->error = error;

	return this;
}

void Net_destruct(struct Net * this)
{
	// fields
	Place_destruct(this->placeSize);
	Place_destruct(this->nextPlace);
	Place_destruct(this->gapPlace);
	
	Mesh_destruct(this->mesh);
	Space_destruct(this->space);
	
	free(this);
	this = NULL;
}

void Net_create(struct Net * this, size_t placeSize)
{
	Net_read(this);

	Place_set(this->placeSize, placeSize);
	Place_set(this->nextPlace, this->entrySize);
	Place_set(this->gapPlace, 0);
}

void Net_read(struct Net * this)
{
	Place_bind(this->placeSize, 1);
	Place_bind(this->nextPlace, 2);
	Place_bind(this->gapPlace, 3);
}

char Net_hasEntry(struct Net * this, size_t place)
{
	if (place < this->entrySize) {
		return 0;
	}
	
	if ( place >= Place_get(this->nextPlace) ) {
		return 0;
	}
	
	return 1;
}

char Net_canCreateEntry(struct Net * this)
{
	return Space_canTakeAnotherEntry(
		this->space, 
		Place_get(this->nextPlace), 
		Place_get(this->gapPlace)
	);
}

size_t Net_createEntry(struct Net * this)
{
	size_t place = Place_get(this->gapPlace);
	
	size_t nextGapPlace;

	if ( 0 != place ) {
		nextGapPlace = Mesh_removeGap(this->mesh, place);
		Place_set(this->gapPlace, nextGapPlace);
	} else {
		place = Place_get(this->nextPlace);
		Place_set(this->nextPlace, place + this->entrySize);
	}

	return place;
}

void Net_deleteEntry(struct Net * this, size_t place)
{
	size_t nextGapPlace = Place_get(this->gapPlace);
	
	Mesh_addGap(this->mesh, place, nextGapPlace);
	
	Place_set(this->gapPlace, place);
}

size_t Net_calculateSize(struct Net * this)
{
	return Place_get(this->placeSize) * Place_get(this->nextPlace);
}

void Net_import(struct Net * this, struct Stream * stream, size_t graphSize)
{
	NetError_requireFittingInSize(this->error, Place_get(this->nextPlace), graphSize);
	
	size_t placeSize = Place_get(this->placeSize);
	size_t nextPlace = Place_get(this->nextPlace);

	size_t offset = this->entrySize * placeSize;
	size_t size = nextPlace * placeSize - offset;
	
	Stream_read(stream, offset, size);
}