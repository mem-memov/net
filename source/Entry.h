#ifndef ENTRY_H
#define ENTRY_H

#include <stdlib.h>

struct Entry;

struct Entry * Entry_construct();

void Entry_destruct(struct Entry * this);

void Entry_read(struct Entry * this, size_t place);

char Entry_isEmpty(struct Entry * this);

#endif