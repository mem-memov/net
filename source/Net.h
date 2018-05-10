#ifndef NET_H
#define NET_H

#include <stdlib.h>
#include <stdio.h>
#include "Count.h"
#include "Gaps.h"
#include "Place.h"

struct Net;

struct Net * Net_construct(
	size_t spaceSize, 
	size_t entrySize, 
	struct Place * entry, 
	struct Gaps * gaps,
	struct Place * one,
	struct Place * placeSize,
	struct Place * nextPlace,
	struct Count * gapCount,
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

void Net_export(struct Net * this, FILE * file);

void Net_import(struct Net * this, FILE * file);

void Net_scanForGaps(struct Net * this);

void Net_addGap(struct Net * this, size_t place);

#endif