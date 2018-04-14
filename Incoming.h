#ifndef INCOMING_H
#define INCOMING_H

#include <stdlib.h>

struct Incoming {
	size_t * places;
	
	size_t place;
	
	size_t * node;
	size_t * previous;
	size_t * next;
};

struct Incoming * Incoming_construct(size_t * places);

void Incoming_destruct(struct Incoming * this);

size_t Incoming_getPlace(struct Incoming * this);

void Incoming_create(struct Incoming * this, size_t place, size_t origin);

void Incoming_read(struct Incoming * this, size_t place);

void Incoming_joinChain(struct Incoming * this, size_t previous, size_t next);

void Incoming_append(struct Incoming * this, size_t previous);

char Incoming_hasNode(struct Incoming * this, size_t node);

size_t Incoming_getNext(struct Incoming * this);

#endif