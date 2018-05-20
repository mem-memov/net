#ifndef DIRECTIONS_H
#define DIRECTIONS_H

#include "Direction.h"
#include "DirectionError.h"
#include "Places.h"

struct Directions;

struct Directions * Directions_construct(struct Places * places, struct DirectionError * directionError);

void Directions_destruct(struct Directions * this);

struct Direction * Directions_makeOutgoing(struct Directions * this);

struct Direction * Directions_makeIncoming(struct Directions * this);

#endif

