#include "Thread.h"
#include <stdlib.h>
#include <pthread.h>

#include <stdio.h>

struct Thread
{
	struct Thread * next;
	char isIdle;
	pthread_t id;
	pthread_attr_t attributes;
};

struct Thread * Thread_construct(struct Thread * next)
{
	struct Thread * this = malloc(sizeof(struct Thread));
	
	this->next = next;
	this->isIdle = 1;
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
	this->isIdle = 0;
	
	pthread_attr_init(&this->attributes);
	
	pthread_create(&this->id, &this->attributes, function, parameter);
	
	printf("Thread %zu started.\n", this->id);
}

void Thread_stop(struct Thread * this)
{
	printf("Thread %zu stopped.\n", this->id);
	
	this->isIdle = 1;
	
	pthread_exit(NULL);
	//pthread_join(this->id, NULL); //?????
}

struct Thread * Thread_getNext(struct Thread * this)
{
	return this->next;
}

char Thread_isIdle(struct Thread * this)
{
	return this->isIdle;
}