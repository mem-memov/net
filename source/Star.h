#ifndef STAR_H
#define STAR_H

#include <stdlib.h>
#include "Link.h"

struct Star;

struct Star * Star_construct(struct Link * incomingLink, struct Link * outgoingLink);

void Star_destruct(struct Star * this);

void Star_addIncomingLink(struct Star * this, size_t oldIncomingLink, size_t newIncomingLink);

void Star_addOutgoingLink(struct Star * this, size_t oldOutgoingLink, size_t newOutgoingLink);

size_t Star_findIncomingLink(struct Star * this, size_t incomingLink, size_t originNode);

size_t Star_findOutgoingLink(struct Star * this, size_t outgoingLink, size_t destinationNode);

void Star_getNodeDestinations(struct Star * this, size_t outgoingLink, size_t * destinations, size_t length);

void Star_getNodeOrigins(struct Star * this, size_t incomingLink, size_t * origins, size_t length);

#endif