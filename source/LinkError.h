#ifndef LINKERROR_H
#define LINKERROR_H

#include <stdlib.h>
#include "Error.h"

struct LinkError;

struct LinkError * LinkError_construct(struct Error * error);

void LinkError_destruct(struct LinkError * this);

void LinkError_forbidSelfPointingNodes(struct LinkError * this, size_t origin, size_t destination);

#endif