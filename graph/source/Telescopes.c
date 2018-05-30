#include "Telescopes.h"
#include <stdlib.h>

struct Telescopes
{
	struct Links * links;
};

struct Telescopes * Telescopes_construct(struct Links * links)
{
	struct Telescopes * this = malloc(sizeof(struct Telescopes));
	
	this->links = links;

	return this;
}

void Telescopes_destruct(struct Telescopes * this)
{
	free(this);
	this = NULL;
}

struct Telescope * Telescopes_make(struct Telescopes * this)
{
	return Telescope_construct(
		Links_make(this->links)
	);
}