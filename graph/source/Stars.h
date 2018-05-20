#ifndef STARS_H
#define STARS_H

#include "Links.h"
#include "Star.h"

struct Stars;

struct Stars * Stars_construct(struct Links * links);

void Stars_destruct(struct Stars * this);

struct Star * Stars_make(struct Stars * this);

#endif