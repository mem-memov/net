#ifndef PARAMETER_H
#define PARAMETER_H

#include "Application.h"
#include "Connection.h"
#include "Thread.h"

struct Parameter;

struct Parameter * Parameter_construct(struct Connection * connection, struct Thread * thread, struct Application * application);

void Parameter_destruct(struct Parameter * this);

struct Connection * Parameter_getConnection(struct Parameter * this);

struct Thread * Parameter_getThread(struct Parameter * this);

struct Application * Parameter_getApplication(struct Parameter * this);

#endif
