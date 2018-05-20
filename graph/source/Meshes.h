#ifndef MESHES_H
#define MESHES_H

#include "Gaps.h"
#include "Mesh.h"

struct Meshes;

struct Meshes * Meshes_construct(struct Gaps * gaps);

void Meshes_destruct(struct Meshes * this);

struct Mesh * Meshes_make(struct Meshes * this);

#endif