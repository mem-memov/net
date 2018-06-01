#include "Nets.h"

struct Nets
{
	struct Meshes * meshes;
	struct Places * places;
	struct Spaces * spaces;
	
	struct NetError * netError;
};

struct Nets * Nets_construct(
	struct Meshes * meshes, 
	struct Places * places, 
	struct Spaces * spaces,
	struct NetError * netError
) {
	struct Nets * this = malloc(sizeof(struct Nets));

	this->meshes = meshes;
	this->places = places;
	this->spaces = spaces;
	this->netError = netError;
	
	return this;
}

void Nets_destruct(struct Nets * this)
{
	free(this);
	this = NULL;
}

struct Net * Nets_make(struct Nets * this, size_t entrySize)
{
	return Net_construct(
		entrySize, 
		Places_make(this->places),
		Places_make(this->places),
		Places_make(this->places),
		Meshes_make(this->meshes),
		Spaces_make(this->spaces),
		this->netError
	);
}