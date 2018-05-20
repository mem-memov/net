#include "Database.h"
#include <stdlib.h>

struct Database
{
	//
};

struct Database * Database_construct()
{
	struct Database * this = malloc(sizeof(struct Database));

	return this;
}

void Database_destruct(struct Database * this)
{
	free(this);
	this = NULL;
}

