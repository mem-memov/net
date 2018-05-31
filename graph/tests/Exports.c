#include "Exports.h"
#include <stdlib.h>

#define EXPORTS_MAX_CALLS 1

struct Exports
{
	char call;
	char * method[EXPORTS_MAX_CALLS];
	size_t size[EXPORTS_MAX_CALLS];
	struct Export * export[EXPORTS_MAX_CALLS];
};

struct Exports * Exports_mock()
{
	struct Exports * this = malloc(sizeof(struct Exports));
	
	this->call = 0;
	
	char i;
	for (i = 0; i < EXPORTS_MAX_CALLS; i++) {
		this->method[i] = "method never called";
		this->size[i] = 55555;
		this->export[i] = NULL;
	}

	return this;
}

void Exports_destruct(struct Exports * this)
{
	free(this);
	this = NULL;
}

struct Export * Exports_make(struct Exports * this, size_t size)
{
	this->method[this->call] = "Exports_make";
	this->size[this->call] = size;
	
	struct Export * export = this->export[this->call];
	
	this->call++;
	
	return export;
}