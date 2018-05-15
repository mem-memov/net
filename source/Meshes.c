#include "Meshes.h"
#include <stdlib.h>

struct Meshes
{
	struct Gaps * gaps;
};

struct Meshes * Meshes_construct(struct Gaps * gaps)
{
	struct Meshes * this = malloc(sizeof(struct Meshes));
	
	this->gaps = gaps;

	return this;
}

void Meshes_destruct(struct Meshes * this)
{
	free(this);
	this = NULL;
}

struct Mesh * Meshes_make(struct Meshes * this)
{
	return Mesh_construct(
		Gaps_make(this->gaps),
		Gaps_make(this->gaps)
	);
}