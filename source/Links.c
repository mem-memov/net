#include "Links.h"
#include <stdlib.h>

struct Links
{
	struct LinkError * linkError;
	struct Directions * directions;
};

struct Links * Links_construct(struct LinkError * linkError, struct Directions * directions)
{
	struct Links * this = malloc(sizeof(struct Links));
	
	this->linkError = linkError;
	this->directions = directions;
	
	return this;
}

void Links_destruct(struct Links * this)
{
	LinkError_destruct(this->linkError);
	
	free(this);
	this = NULL;
}

struct Link * Links_make(struct Links * this)
{
	return Link_construct(
		Directions_makeOutgoing(this->directions),
		Directions_makeIncoming(this->directions),
		this->linkError
	);
}
