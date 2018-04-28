#ifndef LINKERROR_H
#define LINKERROR_H

#include <stdlib.h>

struct LinkError;

struct LinkError * LinkError_construct();

void LinkError_destruct(struct LinkError * this);

void LinkError_forbidSelfPointingNodes(struct LinkError * this, size_t origin, size_t destination);

#endif