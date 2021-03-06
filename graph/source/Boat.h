#ifndef BOAT_H
#define BOAT_H

#include <stdlib.h>
#include "Count.h"
#include "Export.h"
#include "Exports.h"
#include "Net.h"
#include "BoatError.h"
#include "Place.h"
#include "Stream.h"

struct Boat;

struct Boat * Boat_construct(
	size_t graphSize, 
	size_t entrySize, 
	size_t placeSize,
	struct Exports * exports,
	struct Place * one,
	struct Count * nodeCount,
	struct Count * linkCount,
	struct Net * net,
	struct BoatError * error
);

void Boat_destruct(struct Boat * this);

void Boat_create(struct Boat * this);

void Boat_read(struct Boat * this);

char Boat_isCovering(struct Boat * this, size_t place);

char Boat_hasSpaceForEntry(struct Boat * this);

size_t Boat_createLinkEntry(struct Boat * this);

size_t Boat_createNodeEntry(struct Boat * this);

void Boat_deleteLinkEntry(struct Boat * this, size_t place);

void Boat_deleteNodeEntry(struct Boat * this, size_t place);

struct Export * Boat_createExport(struct Boat * this);

void Boat_import(struct Boat * this, struct Stream * stream);

#endif