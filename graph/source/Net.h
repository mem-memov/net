#ifndef NET_H
#define NET_H

#include <stdlib.h>
#include "Count.h"
#include "Export.h"
#include "Exports.h"
#include "Knitter.h"
#include "NetError.h"
#include "Place.h"
#include "Stream.h"

struct Net;

struct Net * Net_construct(
	size_t graphSize, 
	size_t entrySize, 
	struct Exports * exports,
	struct Place * one,
	struct Count * nodeCount,
	struct Count * linkCount,
	struct Knitter * knitter,
	struct NetError * error
);

void Net_destruct(struct Net * this);

void Net_create(struct Net * this, size_t placeSize);

void Net_read(struct Net * this);

char Net_isCovering(struct Net * this, size_t place);

char Net_hasSpaceForEntry(struct Net * this);

size_t Net_createLinkEntry(struct Net * this);

size_t Net_createNodeEntry(struct Net * this);

void Net_deleteLinkEntry(struct Net * this, size_t place);

void Net_deleteNodeEntry(struct Net * this, size_t place);

struct Export * Net_createExport(struct Net * this);

void Net_import(struct Net * this, struct Stream * stream);

#endif