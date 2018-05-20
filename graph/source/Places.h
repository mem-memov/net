#ifndef PLACES_H
#define PLACES_H

#include "Place.h"

struct Places;

struct Places * Places_construct(unsigned char length, unsigned char * bytes);

void Places_destruct(struct Places * this);

struct Place * Places_make(struct Places * this);

#endif

