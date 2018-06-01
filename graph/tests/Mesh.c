#include "../source/Mesh.h"

#define MESH_MAX_CALLS 1

struct Mesh
{
	char call;
	char * method[MESH_MAX_CALLS];
	size_t place[MESH_MAX_CALLS];
	size_t nextGapPlace[MESH_MAX_CALLS];
};

struct Mesh * Mesh_mock()
{
	struct Mesh * this = malloc(sizeof(struct Mesh));
	
	this->call = 0;
	
	char i;
	for (i = 0; i < MESH_MAX_CALLS; i++) {
		this->method[i] = "method never called";
		this->place[i] = 55555;
		this->nextGapPlace[i] = 55555;
	}

	return this;
}

void Mesh_destruct(struct Mesh * this)
{
	free(this);
	this = NULL;
}

void Mesh_addGap(struct Mesh * this, size_t place, size_t nextGapPlace)
{
	this->method[this->call] = "Mesh_addGap";
	this->place[this->call] = place;
	this->nextGapPlace[this->call] = nextGapPlace;
	
	this->call++;
}

size_t Mesh_removeGap(struct Mesh * this, size_t place)
{
	this->method[this->call] = "Mesh_removeGap";
	this->place[this->call] = place;
	
	this->call++;
	
	size_t nextGapPlace = this->nextGapPlace[this->call];
	
	return nextGapPlace;
}