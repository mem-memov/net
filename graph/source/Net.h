#ifndef NET_H
#define NET_H

#include <stdlib.h>
#include "NetError.h"
#include "Mesh.h"
#include "Place.h"
#include "Space.h"
#include "Stream.h"

struct Net;

struct Net * Net_construct(
	size_t entrySize, 
	struct Place * placeSize,
	struct Place * nextPlace,
	struct Place * gapPlace,
	struct Mesh * mesh,
	struct Space * space,
	struct NetError * error
);

void Net_destruct(struct Net * this);

void Net_create(struct Net * this, size_t placeSize);

void Net_read(struct Net * this);

char Net_hasCreatedEntry(struct Net * this, size_t place);

char Net_canCreateEntry(struct Net * this);

size_t Net_createEntry(struct Net * this);

void Net_deleteEntry(struct Net * this, size_t place);

size_t Net_calculateSize(struct Net * this);

void Net_import(struct Net * this, struct Stream * stream, size_t graphSize);

#endif
