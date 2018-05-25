#include "Database.h"
#include <stdlib.h>

struct Database
{
	struct Graph * graph;
	struct Entries * entries;
	struct Collections * collections;
};

struct Database * Database_construct(
	struct Graph * graph, 
	struct Entries * entries, 
	struct Collections * collections
) {
	struct Database * this = malloc(sizeof(struct Database));
	
	this->graph = graph;
	this->entries = entries;
	this->collections = collections;

	return this;
}

void Database_destruct(struct Database * this)
{
	free(this);
	this = NULL;
}

struct Collection * Database_createEntries(struct Database * this, size_t length)
{
	struct Collection * collection = Collections_make(this->collections, length);
	struct Entry * entry;
	size_t node;
	size_t index;
	for ( index = 0; index < length; index++ ) {
		node = Graph_addNode(this->graph);
		entry = Entries_make(this->entries);
		Collection_addEntry(collection, entry);
	}
	
	return collection;
}

