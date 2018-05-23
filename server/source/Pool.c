#include "Pool.h"
#include <stdlib.h>

struct Pool
{
	struct Threads * threads;
	struct Thread * thread;
};

struct Pool * Pool_construct(struct Threads * threads)
{
	struct Pool * this = malloc(sizeof(struct Pool));
	
	this->threads = threads;
	this->thread = NULL;

	return this;
}

void Pool_destruct(struct Pool * this)
{
	Threads_destruct(this->threads);
	
	if ( NULL != this->thread ) {
		struct Thread * thread = this->thread;
		struct Thread * next;
		
		do {
			next = Thread_getNext(this->thread);
			Thread_destruct(thread);
			thread = next;
		} while( NULL != thread );
	}
	
	free(this);
	this = NULL;
}

struct Thread * Pool_getThread(struct Pool * this)
{
	// first thread
	if ( NULL == this->thread ) {
		this->thread = Threads_make(this->threads, NULL);
		return this->thread;
	}

	struct Thread * thread = this->thread;
	
	// idle thread
	do {
		if (Thread_isIdle(thread)) {
			return thread;
		}
		thread = Thread_getNext(this->thread);
	} while( NULL != thread );
	
	// new thread
	thread = Threads_make(this->threads, this->thread);
	this->thread = thread;
	return this->thread;
}