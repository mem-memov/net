#include "Scans.h"
#include <stdlib.h>

struct Scans
{
	//
};

struct Scans * Scans_construct()
{
	struct Scans * this = malloc(sizeof(struct Scans));

	return this;
}

void Scans_destruct(struct Scans * this)
{
	free(this);
	this = NULL;
}

struct Scan * Scans_make(struct Scans * this)
{
	return Scan_construct();
}