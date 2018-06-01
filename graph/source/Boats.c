#include "Boats.h"

struct Boats
{
	struct Places * places;
	struct Counts * counts;
	struct Knitters * knitters;
	struct Exports * exports;
	struct BoatError * boatError;
};

struct Boats * Boats_construct(
	struct Places * places, 
	struct Counts * counts, 
	struct Knitters * knitters, 
	struct Exports * exports,
	struct BoatError * boatError
) {
	struct Boats * this = malloc(sizeof(struct Boats));
	
	this->places = places;
	this->counts = counts;
	this->knitters = knitters;
	this->exports = exports;
	this->boatError = boatError;
	
	return this;
}

void Boats_destruct(struct Boats * this)
{
	Knitters_destruct(this->knitters);
	Exports_destruct(this->exports);
	
	free(this);
	this = NULL;
}

struct Boat * Boats_make(struct Boats * this, size_t graphSize, size_t entrySize)
{
	return Boat_construct(
		graphSize, 
		entrySize, 
		this->exports,
		Places_make(this->places),
		Counts_make(this->counts),
		Counts_make(this->counts),
		Knitters_make(this->knitters, entrySize),
		this->boatError
	);
}
