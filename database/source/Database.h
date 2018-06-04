#ifndef DATABASE_H
#define DATABASE_H

#include <stdlib.h>

struct Database;

void Database_destruct(struct Database * this);

struct Collection * Database_createEntries(struct Database * this, size_t length);

#endif