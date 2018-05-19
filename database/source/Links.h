#ifndef LINKS_H
#define LINKS_H

#include "Link.h"
#include "LinkError.h"
#include "Directions.h"

struct Links;

struct Links * Links_construct(struct LinkError * linkError, struct Directions * directions);

void Links_destruct(struct Links * this);

struct Link * Links_make(struct Links * this);

#endif

