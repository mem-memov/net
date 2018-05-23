#ifndef PARAMETER_H
#define PARAMETER_H

#include "Connection.h"
#include "Thread.h"

struct Parameter;

struct Parameter * Parameter_construct(struct Connection * connection, struct Thread * thread);

void Parameter_destruct(struct Parameter * this);

struct Connection * Parameter_getConnection(struct Parameter * this);

struct Thread * Parameter_getThread(struct Parameter * this);

#endif
