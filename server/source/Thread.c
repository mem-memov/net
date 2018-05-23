#include "Thread.h"
#include <stdlib.h>
#include <pthread.h>

#include <stdio.h>

struct Thread
{
	pthread_t id;
	pthread_attr_t attributes;
};

struct Thread * Thread_construct()
{
	struct Thread * this = malloc(sizeof(struct Thread));

	//this->id = NULL;

	return this;
}

void Thread_destruct(struct Thread * this)
{
	free(this);
	this = NULL;
}

void Thread_start(struct Thread * this, void * (* function) (void *), void * parameter)
{
	pthread_attr_init(&this->attributes);
	
	pthread_create(&this->id, &this->attributes, function, parameter);
	
	printf("Thread %zu started.\n", this->id);
}

void Thread_stop(struct Thread * this)
{
	printf("Thread %zu stopped.\n", this->id);

	pthread_exit(NULL);
	pthread_join(this->id, NULL);
	
	Thread_destruct(this);
}
