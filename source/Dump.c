#include "Dump.h"
#include <stdlib.h>
#include <stdio.h>

struct Dump
{
	size_t * places;
	FILE * file;
};

struct Dump * Dump_construct(size_t * places, FILE * file)
{
	struct Dump * this = malloc(sizeof(struct Dump));
	
	this->places = places;
	this->file = file;
	
	return this;
}

void Dump_destruct(struct Dump * this)
{
	free(this);
	this = NULL;
}

void Dump_export(struct Dump * this)
{
	
}

void Dump_import(struct Dump * this)
{
	
}