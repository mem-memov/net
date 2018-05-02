#ifndef GAPS_H
#define GAPS_H

#include <stdlib.h>
#include "GapError.h"

struct Gaps;

struct Gaps * Gaps_construct(struct GapError * gapError);

void Gaps_destruct(struct Gaps * this);

void Gaps_addGap(struct Gaps * this, size_t place);

char Gaps_areEmpty(struct Gaps * this);

size_t Gaps_givePlace(struct Gaps * this);

#endif