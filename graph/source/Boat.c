#include "Boat.h"

struct Boat {
	size_t graphSize;
	size_t entrySize;
	
	struct Exports * exports;
	
	struct Place * one;
	struct Count * nodeCount;
	struct Count * linkCount;
	
	struct Knitter * knitter;
	
	struct BoatError * error;
};

struct Boat * Boat_construct(
	size_t graphSize, 
	size_t entrySize, 
	struct Exports * exports,
	struct Place * one,
	struct Count * nodeCount,
	struct Count * linkCount,
	struct Knitter * knitter,
	struct BoatError * error
) {
	struct Boat * this = malloc(sizeof(struct Boat));

	this->graphSize = graphSize;
	this->entrySize = entrySize;

	this->exports = exports;
	
	// fields
	this->one = one;
	this->nodeCount = nodeCount;
	this->linkCount = linkCount;
	
	this->knitter = knitter;
	
	this->error = error;

	return this;
}

void Boat_destruct(struct Boat * this)
{
	Place_destruct(this->one);
	Count_destruct(this->nodeCount);
	Count_destruct(this->linkCount);
	
	Knitter_destruct(this->knitter);
	
	free(this);
	this = NULL;
}

void Boat_create(struct Boat * this, size_t placeSize)
{
	Boat_read(this);
	
	Place_set(this->one, 1);
	Knitter_create(this->knitter, placeSize);
	Count_create(this->nodeCount);
	Count_create(this->linkCount);
}

void Boat_read(struct Boat * this)
{
	Place_bind(this->one, 0);
	Knitter_read(this->knitter);
	Count_bind(this->nodeCount, 4);
	Count_bind(this->linkCount, 5);
}

char Boat_isCovering(struct Boat * this, size_t place)
{
	return Knitter_hasCreatedEntry(this->knitter, place);
}

char Boat_hasSpaceForEntry(struct Boat * this)
{
	return Knitter_canCreateEntry(this->knitter);
}

size_t Boat_createLinkEntry(struct Boat * this)
{
	BoatError_requireFreeSpaceAvailable(
		this->error,
		Knitter_canCreateEntry(this->knitter)
	);

	size_t place = Knitter_createEntry(this->knitter);

	Count_increment(this->linkCount);

	return place;
}

size_t Boat_createNodeEntry(struct Boat * this)
{
	BoatError_requireFreeSpaceAvailable(
		this->error,
		Knitter_canCreateEntry(this->knitter)
	);

	size_t place = Knitter_createEntry(this->knitter);

	Count_increment(this->nodeCount);

	return place;
}

void Boat_deleteLinkEntry(struct Boat * this, size_t place)
{
	Knitter_deleteEntry(this->knitter, place);

	Count_decrement(this->linkCount);
}

void Boat_deleteNodeEntry(struct Boat * this, size_t place)
{
	Knitter_deleteEntry(this->knitter, place);

	Count_decrement(this->nodeCount);
}

struct Export * Boat_createExport(struct Boat * this)
{
	size_t size = Knitter_calculateSize(this->knitter);
	
	return Exports_make(this->exports, size);
}

void Boat_import(struct Boat * this, struct Stream * stream)
{
	BoatError_requireOboatoVerifyCorrectPlaceSize(this->error, Place_get(this->one));
	
	Knitter_import(this->knitter, stream, this->graphSize);
}