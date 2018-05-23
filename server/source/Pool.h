#ifndef POOL_H
#define POOL_H

#include "Thread.h"
#include "Threads.h"

struct Pool;

struct Pool * Pool_construct(struct Threads * threads);

void Pool_destruct(struct Pool * this);

struct Thread * Pool_getThread(struct Pool * this);

#endif
