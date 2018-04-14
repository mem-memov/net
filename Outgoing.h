#ifndef OUTGOING_H
#define OUTGOING_H

#include <stdlib.h>

struct Outgoing {
	size_t * places;
	
	size_t place;
	
	size_t * node;
	size_t * previous;
	size_t * next;
};

struct Outgoing * Outgoing_construct(size_t * places);

size_t Outgoing_getPlace(struct Outgoing * this);

void Outgoing_destruct(struct Outgoing * this);

void Outgoing_create(struct Outgoing * this, size_t place, size_t destination);

void Outgoing_read(struct Outgoing * this, size_t place);

void Outgoing_joinChain(struct Outgoing * this, size_t previous, size_t next);

void Outgoing_append(struct Outgoing * this, size_t previous);

char Outgoing_hasNode(struct Outgoing * this, size_t node);

size_t Outgoing_getNode(struct Outgoing * this);

size_t Outgoing_getNext(struct Outgoing * this);

#endif