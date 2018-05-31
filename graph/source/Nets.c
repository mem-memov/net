#include "Nets.h"
#include <stdlib.h>

struct Nets
{
	struct Places * places;
	struct Counts * counts;
	struct Meshes * meshes;
	struct Exports * exports;
	struct NetError * netError;
};

struct Nets * Nets_construct(
	struct Places * places, 
	struct Counts * counts, 
	struct Meshes * meshes, 
	struct Exports * exports,
	struct NetError * netError
) {
	struct Nets * this = malloc(sizeof(struct Nets));
	
	this->places = places;
	this->counts = counts;
	this->meshes = meshes;
	this->exports = exports;
	this->netError = netError;
	
	return this;
}

void Nets_destruct(struct Nets * this)
{
	Meshes_destruct(this->meshes);
	Exports_destruct(this->exports);
	
	free(this);
	this = NULL;
}

struct Net * Nets_make(struct Nets * this, size_t graphSize, size_t entrySize)
{
	return Net_construct(
		graphSize, 
		entrySize, 
		Meshes_make(this->meshes),
		this->exports,
		Places_make(this->places),
		Places_make(this->places),
		Places_make(this->places),
		Places_make(this->places),
		Counts_make(this->counts),
		Counts_make(this->counts),
		this->netError
	);
}
