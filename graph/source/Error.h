#ifndef ERROR_H
#define ERROR_H

struct Error;

struct Error * Error_construct();

void Error_destruct(struct Error * this);

void Error_terminate(struct Error * this);

#endif

