#include "Signal.h"
#include <stdlib.h>
#include <signal.h>

struct Signal {
    int code;
    void (*handler)(int);
};

struct Signal * Signal_constructSigint(void (*handler)(int))
{
	struct Signal * this = malloc(sizeof(struct Signal));

	this->code = SIGINT;
	this->handler = handler;

	return this;
}

void Signal_destruct(struct Signal * this)
{
    free(this);
	this = NULL;
}

int Signal_catch(struct Signal * this)
{
    struct sigaction action;
    action.sa_handler = this->handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    return sigaction(this->code, &action, NULL);
}
