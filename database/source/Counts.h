#ifndef COUNTS_H
#define COUNTS_H

#include "Count.h"
#include "CountError.h"
#include "Places.h"

struct Counts;

struct Counts * Counts_construct(struct Places * places, struct CountError * countError);

void Counts_destruct(struct Counts * this);

struct Count * Counts_make(struct Counts * this);

#endif