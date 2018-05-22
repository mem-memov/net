#ifndef THREAD_H
#define THREAD_H

struct Thread;

struct Thread * Thread_construct();

void Thread_destruct(struct Thread * this);

void Thread_start(struct Thread * this, void * (* function) (void *), void * parameter);

#endif
