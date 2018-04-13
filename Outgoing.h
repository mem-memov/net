#ifndef OUTGOING_H
#define OUTGOING_H

struct Outgoing {
	size_t * places;
	
	size_t place;
	
	size_t * node;
	size_t * previous;
	size_t * next;
};

struct Outgoing * Outgoing_construct(size_t * places);

void Outgoing_destruct(struct Outgoing * this);

void Outgoing_create(struct Outgoing * this, size_t place, size_t destination);

#endif