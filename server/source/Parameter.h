#ifndef PARAMETER_H
#define PARAMETER_H

#include "Application.h"
#include "Listener.h"

struct Parameter;

struct Parameter * Parameter_construct(
    struct Listener * listener, 
    int bufferLength,
    struct Application * application
);

void Parameter_destruct(struct Parameter * this);

struct Listener * Parameter_getListener(struct Parameter * this);

int Parameter_getBufferLength(struct Parameter * this);

struct Application * Parameter_getApplication(struct Parameter * this);

#endif
