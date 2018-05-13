#include "Nets.h"
#include <stdlib.h>

struct Nets
{
	struct Places * places;
	struct Counts * counts;
	struct Gaps * gaps;
	struct Exports * exports;
	struct Scans * scans;
};

struct Nets * Nets_construct(
	struct Places * places, 
	struct Counts * counts, 
	struct Gaps * gaps, 
	struct Exports * exports,
	struct Scans * scans
) {
	struct Nets * this = malloc(sizeof(struct Nets));
	
	this->places = places;
	this->counts = counts;
	this->gaps = gaps;
	this->exports = exports;
	this->scans = scans;
	
	return this;
}

void Nets_destruct(struct Nets * this)
{
	Gaps_destruct(this->gaps);
	Exports_destruct(this->exports);
	Scans_destruct(this->scans);
	
	free(this);
	this = NULL;
}

struct Net * Nets_make(struct Nets * this, size_t spaceSize, size_t entrySize)
{
	return Net_construct(
		spaceSize, 
		entrySize, 
		Places_make(this->places), 
		this->gaps,
		this->exports,
		Scans_make(this->scans),
		Places_make(this->places),
		Places_make(this->places),
		Places_make(this->places),
		Counts_make(this->counts),
		Counts_make(this->counts),
		Counts_make(this->counts)
	);
}
