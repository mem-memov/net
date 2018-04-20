#ifndef DIRECTIONERROR_H
#define DIRECTIONERROR_H

struct DirectionError;

struct DirectionError * DirectionError_construct();

void DirectionError_destruct(struct DirectionError * this);

#endif

