#ifndef THREAD_H
#define THREAD_H

struct Thread;

struct Thread * Thread_construct();

void Thread_destruct(struct Thread * this);

void Thread_start(struct Thread * this, void * (* function) (void *), void * parameter);

void Thread_stop(struct Thread * this);

struct Thread * Thread_getNext(struct Thread * this);

char Thread_isIdle(struct Thread * this);

#endif
