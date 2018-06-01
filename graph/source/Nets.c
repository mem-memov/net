#include "Nets.h"

struct Nets
{
	struct Places * places;
	struct Counts * counts;
	struct Knitters * knitters;
	struct Exports * exports;
	struct NetError * netError;
};

struct Nets * Nets_construct(
	struct Places * places, 
	struct Counts * counts, 
	struct Knitters * knitters, 
	struct Exports * exports,
	struct NetError * netError
) {
	struct Nets * this = malloc(sizeof(struct Nets));
	
	this->places = places;
	this->counts = counts;
	this->knitters = knitters;
	this->exports = exports;
	this->netError = netError;
	
	return this;
}

void Nets_destruct(struct Nets * this)
{
	Knitters_destruct(this->knitters);
	Exports_destruct(this->exports);
	
	free(this);
	this = NULL;
}

struct Net * Nets_make(struct Nets * this, size_t graphSize, size_t entrySize)
{
	return Net_construct(
		graphSize, 
		entrySize, 
		this->exports,
		Places_make(this->places),
		Places_make(this->places),
		Counts_make(this->counts),
		Counts_make(this->counts),
		Knitters_make(this->knitters, entrySize),
		this->netError
	);
}
