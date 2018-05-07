#ifndef NETS_H
#define NETS_H

#include "Gaps.h"
#include "Net.h"
#include "Places.h"

struct Nets;

struct Nets * Nets_construct(struct Places * places, struct Gaps * gaps);

void Nets_destruct(struct Nets * this);

struct Net * Nets_make(struct Nets * this, size_t spaceSize, size_t entrySize);

#endif

