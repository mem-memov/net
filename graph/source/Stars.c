#include "Stars.h"
#include <stdlib.h>

struct Stars
{
	struct Links * links;
	struct Telescopes * telescopes;
	struct StarError * starError;
};

struct Stars * Stars_construct(
	struct Links * links, 
	struct Telescopes * telescopes, 
	struct StarError * starError
) {
	struct Stars * this = malloc(sizeof(struct Stars));
	
	this->links = links;
	this->telescopes = telescopes;
	this->starError = starError;

	return this;
}

void Stars_destruct(struct Stars * this)
{
	Telescopes_destruct(this->telescopes);
	
	free(this);
	this = NULL;
}

struct Star * Stars_make(struct Stars * this)
{
	return Star_construct(
		Links_make(this->links),
		Links_make(this->links),
		Telescopes_make(this->telescopes),
		this->starError
	);
}