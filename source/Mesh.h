#ifndef MESH_H
#define MESH_H

#include <stdlib.h>
#include "Gap.h"

struct Mesh;

struct Mesh * Mesh_construct(struct Gap * gap, struct Gap * nextGap);

void Mesh_destruct(struct Mesh * this);

void Mesh_addGap(struct Mesh * this, size_t place, size_t nextGapPlace);

size_t Mesh_removeGap(struct Mesh * this, size_t place);

#endif