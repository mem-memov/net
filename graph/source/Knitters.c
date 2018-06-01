#include "Knitters.h"

struct Knitters
{
	struct Meshes * meshes;
	struct Places * places;
	struct Spaces * spaces;
};

struct Knitters * Knitters_construct(
	struct Meshes * meshes, 
	struct Places * places, 
	struct Spaces * spaces
) {
	struct Knitters * this = malloc(sizeof(struct Knitters));

	this->meshes = meshes;
	this->places = places;
	this->spaces = spaces;
	
	return this;
}

void Knitters_destruct(struct Knitters * this)
{
	free(this);
	this = NULL;
}

struct Knitter * Knitters_make(struct Knitters * this, size_t entrySize)
{
	return Knitter_construct(
		entrySize, 
		Places_make(this->places),
		Places_make(this->places),
		Meshes_make(this->meshes),
		Spaces_make(this->spaces)
	);
}