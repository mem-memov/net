#ifndef DATABASE_H
#define DATABASE_H

#include <netgraph.h>
#include "Collection.h"
#include "Collections.h"
#include "Entries.h"

struct Database;

struct Database * Database_construct(
	struct Graph * graph, 
	struct Entries * entries, 
	struct Collections * collections
);

void Database_destruct(struct Database * this);

struct Collection * Database_createEntries(struct Database * this, size_t length);

#endif