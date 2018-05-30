#ifndef STARS_H
#define STARS_H

#include "Links.h"
#include "Star.h"
#include "Star.h"
#include "StarError.h"

struct Stars;

struct Stars * Stars_construct(struct Links * links, struct StarError * starError);

void Stars_destruct(struct Stars * this);

struct Star * Stars_make(struct Stars * this);

#endif