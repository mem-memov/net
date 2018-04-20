#ifndef DIRECTION_H
#define DIRECTION_H

#include <stdlib.h>
#include "DirectionError.h"

struct Direction;

struct Direction * Direction_constructOutgoing(size_t * places, struct DirectionError * error);

struct Direction * Direction_constructIncoming(size_t * places, struct DirectionError * error);

void Direction_setPool(struct Direction * this, struct Direction * nextDirection);

size_t Direction_getPlace(struct Direction * this);

void Direction_destruct(struct Direction * this);

void Direction_create(struct Direction * this, size_t place, size_t destination);

void Direction_read(struct Direction * this, size_t place);

void Direction_joinChain(struct Direction * this, size_t previous, size_t next);

void Direction_append(struct Direction * this, size_t previous);

char Direction_hasNode(struct Direction * this, size_t node);

size_t Direction_getNode(struct Direction * this);

size_t Direction_getNext(struct Direction * this);

void Direction_delete(struct Direction * this);

#endif