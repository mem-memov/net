#ifndef EXPORTS_H
#define EXPORTS_H

#include "Export.h"

struct Exports;

struct Exports * Exports_construct(unsigned char * bytes);

void Exports_destruct(struct Exports * this);

struct Export * Exports_make(struct Exports * this, size_t size);

#endif