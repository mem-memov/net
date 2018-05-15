#include "Mesh.h"

struct Mesh
{
	struct Gap * gap;
	struct Gap * nextGap;
};

struct Mesh * Mesh_construct(struct Gap * gap, struct Gap * nextGap)
{
	struct Mesh * this = malloc(sizeof(struct Mesh));
	
	this->gap = gap;
	this->nextGap = nextGap;

	return this;
}

void Mesh_destruct(struct Mesh * this)
{
	Gap_destruct(this->gap);
	Gap_destruct(this->nextGap);
	
	free(this);
	this = NULL;
}

void Mesh_addGap(struct Mesh * this, size_t place, size_t nextGapPlace)
{
	Gap_read(this->nextGap, nextGapPlace);
	
	size_t count = Gap_increment(this->nextGap);
	
	Gap_create(this->gap, place, nextGapPlace, count);
}

size_t Mesh_removeGap(struct Mesh * this, size_t place)
{
	Gap_read(this->gap, place);
	
	size_t nextGapPlace = Gap_getNext(this->gap);
	
	Gap_delete(this->gap);
	
	return nextGapPlace;
}