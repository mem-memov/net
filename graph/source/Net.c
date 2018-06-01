#include "Net.h"

struct Net {
	size_t graphSize;
	size_t entrySize;
	
	struct Exports * exports;
	
	struct Place * one;
	struct Count * nodeCount;
	struct Count * linkCount;
	
	struct Knitter * knitter;
	
	struct NetError * error;
};

struct Net * Net_construct(
	size_t graphSize, 
	size_t entrySize, 
	struct Exports * exports,
	struct Place * one,
	struct Count * nodeCount,
	struct Count * linkCount,
	struct Knitter * knitter,
	struct NetError * error
) {
	struct Net * this = malloc(sizeof(struct Net));

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

void Net_destruct(struct Net * this)
{
	Place_destruct(this->one);
	Count_destruct(this->nodeCount);
	Count_destruct(this->linkCount);
	
	Knitter_destruct(this->knitter);
	
	free(this);
	this = NULL;
}

void Net_create(struct Net * this, size_t placeSize)
{
	Net_read(this);
	
	Place_set(this->one, 1);
	Knitter_create(this->knitter, placeSize);
	Count_create(this->nodeCount);
	Count_create(this->linkCount);
}

void Net_read(struct Net * this)
{
	Place_bind(this->one, 0);
	Knitter_read(this->knitter);
	Count_bind(this->nodeCount, 4);
	Count_bind(this->linkCount, 5);
}

char Net_isCovering(struct Net * this, size_t place)
{
	return Knitter_hasCreatedEntry(this->knitter, place);
}

char Net_hasSpaceForEntry(struct Net * this)
{
	return Knitter_canCreateEntry(this->knitter);
}

size_t Net_createLinkEntry(struct Net * this)
{
	NetError_requireFreeSpaceAvailable(
		this->error,
		Knitter_canCreateEntry(this->knitter)
	);

	size_t place = Knitter_createEntry(this->knitter);

	Count_increment(this->linkCount);

	return place;
}

size_t Net_createNodeEntry(struct Net * this)
{
	NetError_requireFreeSpaceAvailable(
		this->error,
		Knitter_canCreateEntry(this->knitter)
	);

	size_t place = Knitter_createEntry(this->knitter);

	Count_increment(this->nodeCount);

	return place;
}

void Net_deleteLinkEntry(struct Net * this, size_t place)
{
	Knitter_deleteEntry(this->knitter, place);

	Count_decrement(this->linkCount);
}

void Net_deleteNodeEntry(struct Net * this, size_t place)
{
	Knitter_deleteEntry(this->knitter, place);

	Count_decrement(this->nodeCount);
}

struct Export * Net_createExport(struct Net * this)
{
	size_t size = Knitter_calculateSize(this->knitter);
	
	return Exports_make(this->exports, size);
}

void Net_import(struct Net * this, struct Stream * stream)
{
	NetError_requireOneToVerifyCorrectPlaceSize(this->error, Place_get(this->one));
	
	Knitter_import(this->knitter, stream, this->graphSize);
}