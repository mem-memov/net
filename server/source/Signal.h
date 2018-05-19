#ifndef SIGNAL_HEADER
#define SIGNAL_HEADER

struct Signal;

struct Signal * Signal_constructSigint(void (*handler)(int));

void Signal_destruct(struct Signal * this);

int Signal_catch(struct Signal * this);

#endif
