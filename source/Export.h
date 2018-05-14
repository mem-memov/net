#ifndef EXPORT_H
#define EXPORT_H

#include <stdio.h>
#include "Streams.h"

struct Export;

struct Export * Export_construct(struct Streams * streams, size_t size);

void Export_destruct(struct Export * this);

void Export_write(struct Export * this, FILE * file);

#endif