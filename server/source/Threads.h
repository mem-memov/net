#ifndef THREADS_H
#define THREADS_H

#include "Thread.h"

struct Threads;

struct Threads * Threads_construct();

void Threads_destruct(struct Threads * this);

struct Thread * Threads_make(struct Threads * this);

#endif
