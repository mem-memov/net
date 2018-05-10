#ifndef COUNT_H
#define COUNT_H

#include <stdlib.h>
#include "CountError.h"
#include "Places.h"

struct Count;

struct Count * Count_construct(struct Place * place, struct CountError * error);

void Count_destruct(struct Count * this);

void Count_bind(struct Count * this, size_t position);

void Count_create(struct Count * this);

void Count_delete(struct Count * this);

void Count_increment(struct Count * this);

void Count_decrement(struct Count * this);

char Count_isZero(struct Count * this);

size_t Count_get(struct Count * this);

#endif