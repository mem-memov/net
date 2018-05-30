#ifndef TELESCOPES_H
#define TELESCOPES_H

#include "Links.h"
#include "Telescope.h"

struct Telescopes;

struct Telescopes * Telescopes_construct(struct Links * links);

void Telescopes_destruct(struct Telescopes * this);

struct Telescope * Telescopes_make(struct Telescopes * this);

#endif
