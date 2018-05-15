#ifndef GAPS_H
#define GAPS_H

#include "Gap.h"
#include "Places.h"

struct Gaps;

struct Gaps * Gaps_construct(struct Places * places);

void Gaps_destruct(struct Gaps * this);

struct Gap * Gaps_make(struct Gaps * this);

#endif