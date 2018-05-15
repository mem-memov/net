#ifndef NET_H
#define NET_H

#include <stdlib.h>
#include "Count.h"
#include "Export.h"
#include "Exports.h"
#include "Mesh.h"
#include "Place.h"
#include "Stream.h"

struct Net;

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
);

void Net_destruct(struct Net * this);

void Net_create(struct Net * this, size_t placeSize);

void Net_read(struct Net * this);

char Net_isHead(struct Net * this, size_t place);

char Net_isInside(struct Net * this, size_t place);

char Net_isSpaceCut(struct Net * this);

char Net_hasSpaceForEntry(struct Net * this);

size_t Net_createEntry(struct Net * this);

void Net_incrementNodes(struct Net * this);

void Net_decrementNodes(struct Net * this);

void Net_incrementLinks(struct Net * this);

void Net_decrementLinks(struct Net * this);

struct Export * Net_createExport(struct Net * this);

void Net_import(struct Net * this, struct Stream * stream);

void Net_addGap(struct Net * this, size_t place);

#endif