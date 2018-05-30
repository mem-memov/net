#ifndef TELESCOPE_H
#define TELESCOPE_H

#include <stdlib.h>
#include "Link.h"

struct Telescope;

struct Telescope * Telescope_construct(struct Link * link);

void Telescope_destruct(struct Telescope * this);

size_t Telescope_findIncomingLink(struct Telescope * this, size_t incomingLink, size_t originNode);

size_t Telescope_findOutgoingLink(struct Telescope * this, size_t outgoingLink, size_t destinationNode);

#endif
