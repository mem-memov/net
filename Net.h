#ifndef NET_H
#define NET_H

struct Net {
	size_t * places;
	size_t spaceSize;
	size_t entrySize;	
	
	size_t one;
	size_t data;
	size_t placeSize;
	size_t nextPlace;
	size_t nodeCount;
	size_t linkCount;
};

struct Net * Net_construct(size_t * places, size_t spaceSize, size_t entrySize);

void Net_destruct(struct Net * this);

void Net_create(struct Net * this, size_t placeSize);

char Net_hasSpaceForEntry(struct Net * this);

size_t Net_createEntry(struct Net * this, struct Gap * gap);

void Net_incrementNodes(struct Net * this);

void Net_decrementNodes(struct Net * this);

void Net_incrementLinks(struct Net * this);

void Net_decrementLinks(struct Net * this);

#endif