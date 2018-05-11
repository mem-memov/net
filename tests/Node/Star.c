#include "../../source/Star.h"
#include <stdlib.h>

struct Star
{

};

struct Star * Star_mock()
{
	struct Star * this = malloc(sizeof(struct Star));


	return this;
}

void Star_destruct(struct Star * this)
{
	free(this);
	this = NULL;
}

void Star_addIncomingLink(struct Star * this, size_t oldIncomingLink, size_t newIncomingLink)
{

}

void Star_addOutgoingLink(struct Star * this, size_t oldOutgoingLink, size_t newOutgoingLink)
{

}

size_t Star_findIncomingLink(struct Star * this, size_t incomingLink, size_t originNode)
{
	return 0;
}

size_t Star_findOutgoingLink(struct Star * this, size_t outgoingLink, size_t destinationNode)
{
	return 0;
}