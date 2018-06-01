#include "Knitter.h"

struct Knitter
{
	size_t entrySize;
	
	// fields
	struct Place * placeSize;
	struct Place * nextPlace;
	struct Place * gapPlace;
	
	struct Mesh * mesh;
	struct Space * space;
};

struct Knitter * Knitter_construct(
	size_t entrySize, 
	struct Place * placeSize,
	struct Place * nextPlace,
	struct Place * gapPlace,
	struct Mesh * mesh,
	struct Space * space
) {
	struct Knitter * this = malloc(sizeof(struct Knitter));
	
	this->entrySize = entrySize;
	
	// fields
	this->placeSize = placeSize;
	this->nextPlace = nextPlace;
	this->gapPlace = gapPlace;
	
	this->mesh = mesh;
	this->space = space;

	return this;
}

void Knitter_destruct(struct Knitter * this)
{
	// fields
	Place_destruct(this->placeSize);
	Place_destruct(this->nextPlace);
	Place_destruct(this->gapPlace);
	
	free(this);
	this = NULL;
}

void Knitter_create(struct Knitter * this, size_t placeSize)
{
	Knitter_read(this);

	Place_set(this->placeSize, placeSize);
	Place_set(this->nextPlace, this->entrySize);
	Place_set(this->gapPlace, 0);
}

void Knitter_read(struct Knitter * this)
{
	Place_bind(this->placeSize, 1);
	Place_bind(this->nextPlace, 2);
	Place_bind(this->gapPlace, 3);
}

char Knitter_hasCreatedEntry(struct Knitter * this, size_t place)
{
	if (place < this->entrySize) {
		return 0;
	}
	
	if ( place >= Place_get(this->nextPlace) ) {
		return 0;
	}
	
	return 1;
}

char Knitter_canCreateEntry(struct Knitter * this)
{
	return Space_canTakeAnotherEntry(
		this->space, 
		Place_get(this->nextPlace), 
		Place_get(this->gapPlace)
	);
}

size_t Knitter_createEntry(struct Knitter * this)
{
	size_t place = Place_get(this->gapPlace);
	
	size_t nextGapPlace;

	if ( 0 != place ) {
		nextGapPlace = Mesh_removeGap(this->mesh, place);
		Place_set(this->gapPlace, nextGapPlace);
	} else {
		place = Place_get(this->nextPlace);
		Place_set(this->nextPlace, Place_get(this->nextPlace) + this->entrySize);
	}

	return place;
}

void Knitter_deleteEntry(struct Knitter * this, size_t place)
{
	size_t nextGapPlace = Place_get(this->gapPlace);
	
	Mesh_addGap(this->mesh, place, nextGapPlace);
	
	Place_set(this->gapPlace, place);
}

size_t Knitter_calculateSize(struct Knitter * this)
{
	return Place_get(this->placeSize) * Place_get(this->nextPlace);
}