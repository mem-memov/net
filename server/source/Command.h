#ifndef COMMAND_H
#define COMMAND_H

#include "Help.h"

struct Command;

struct Command * Command_construct(int count, char ** values, struct Help * help);

void Command_destruct(struct Command * this);

void Command_getParameters(
    struct Command * this, 
    int * port,
    int * connectionLimit,
    int * bufferLength,
    int * threadNumber
);

#endif