#ifndef ENTRIES_H
#define ENTRIES_H

#include "Entry.h"

struct Entries;

struct Entries * Entries_construct();

void Entries_destruct(struct Entries * this);

struct Entry * Entries_make(struct Entries * this);

#endif