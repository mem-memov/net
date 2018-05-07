#ifndef PLACE_H
#define PLACE_H

struct Place;

struct Place * Place_construct(unsigned char length, unsigned char * bytes);

void Place_destruct(struct Place * this);

void Place_bind(struct Place * this, size_t position);

size_t Place_get(struct Place * this);

void Place_set(struct Place * this, size_t value);

char Place_isZero(struct Place * this);

char Place_keepsPosition(struct Place * this);

void Place_increment(struct Place * this);

void Place_decrement(struct Place * this);

#endif

