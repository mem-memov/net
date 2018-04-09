#include "File.h"
#include <stdlib.h>

struct File * File_construct()
{
	struct File * this = malloc(sizeof(struct File));

	return this;
}

void File_destruct(struct File * this)
{
	free(this);
}

