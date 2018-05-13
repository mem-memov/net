#ifndef ENTRY_H
#define ENTRY_H

struct Entry;

struct Entry * Entry_construct();

void Entry_destruct(struct Entry * this);

#endif