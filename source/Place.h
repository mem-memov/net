#ifndef PLACE_H
#define PLACE_H

struct Place;

struct Place * Place_construct(unsigned char length);

void Place_destruct(struct Place * this);

#endif

