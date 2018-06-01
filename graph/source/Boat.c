#include "Boat.h"

struct Boat {
	size_t graphSize;
	size_t entrySize;
	
	struct Exports * exports;
	
	struct Place * one;
	struct Count * nodeCount;
	struct Count * linkCount;
	
	struct Net * net;
	
	struct BoatError * error;
};

struct Boat * Boat_construct(
	size_t graphSize, 
	size_t entrySize, 
	struct Exports * exports,
	struct Place * one,
	struct Count * nodeCount,
	struct Count * linkCount,
	struct Net * net,
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
	
	this->net = net;
	
	this->error = error;

	return this;
}

void Boat_destruct(struct Boat * this)
{
	Place_destruct(this->one);
	Count_destruct(this->nodeCount);
	Count_destruct(this->linkCount);
	
	Net_destruct(this->net);
	
	free(this);
	this = NULL;
}

void Boat_create(struct Boat * this, size_t placeSize)
{
	Boat_read(this);
	
	Place_set(this->one, 1);
	Net_create(this->net, placeSize);
	Count_create(this->nodeCount);
	Count_create(this->linkCount);
}

void Boat_read(struct Boat * this)
{
	Place_bind(this->one, 0);
	Net_read(this->net);
	Count_bind(this->nodeCount, 4);
	Count_bind(this->linkCount, 5);
}

char Boat_isCovering(struct Boat * this, size_t place)
{
	return Net_hasCreatedEntry(this->net, place);
}

char Boat_hasSpaceForEntry(struct Boat * this)
{
	return Net_canCreateEntry(this->net);
}

size_t Boat_createLinkEntry(struct Boat * this)
{
	BoatError_requireFreeSpaceAvailable(
		this->error,
		Net_canCreateEntry(this->net)
	);

	size_t place = Net_createEntry(this->net);

	Count_increment(this->linkCount);

	return place;
}

size_t Boat_createNodeEntry(struct Boat * this)
{
	BoatError_requireFreeSpaceAvailable(
		this->error,
		Net_canCreateEntry(this->net)
	);

	size_t place = Net_createEntry(this->net);

	Count_increment(this->nodeCount);

	return place;
}

void Boat_deleteLinkEntry(struct Boat * this, size_t place)
{
	Net_deleteEntry(this->net, place);

	Count_decrement(this->linkCount);
}

void Boat_deleteNodeEntry(struct Boat * this, size_t place)
{
	Net_deleteEntry(this->net, place);

	Count_decrement(this->nodeCount);
}

struct Export * Boat_createExport(struct Boat * this)
{
	size_t size = Net_calculateSize(this->net);
	
	return Exports_make(this->exports, size);
}

void Boat_import(struct Boat * this, struct Stream * stream)
{
	BoatError_requireOboatoVerifyCorrectPlaceSize(this->error, Place_get(this->one));
	
	Net_import(this->net, stream, this->graphSize);
}