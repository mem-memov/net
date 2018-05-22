#include "Threads.h"
#include <stdlib.h>

struct Threads
{
	//
};

struct Threads * Threads_construct()
{
	struct Threads * this = malloc(sizeof(struct Threads));

	return this;
}

void Threads_destruct(struct Threads * this)
{
	free(this);
	this = NULL;
}

struct Thread * Threads_make(struct Threads * this)
{
	return Thread_construct();
}