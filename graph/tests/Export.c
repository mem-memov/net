#include "Export.h"
#include <stdlib.h>

#define EXPORT_MAX_CALLS 1

struct Export
{
	char call;
	char * method[EXPORT_MAX_CALLS];
	FILE * file[EXPORT_MAX_CALLS];
};

struct Export * Export_mock()
{
	struct Export * this = malloc(sizeof(struct Export));
	
	this->call = 0;
	
	char i;
	for (i = 0; i < EXPORT_MAX_CALLS; i++) {
		this->method[i] = "method never called";
		this->file[i] = NULL;
	}

	return this;
}

void Export_destruct(struct Export * this)
{
	free(this);
	this = NULL;
}

void Export_write(struct Export * this, FILE * file)
{
	this->method[this->call] = "Export_write";
	this->file[this->call] = file;
	
	this->call++;
}