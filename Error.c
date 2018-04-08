#include "Error.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Error * Error_construct()
{
	struct Error * this = malloc(sizeof(struct Error));

	return this;
}

void Error_destruct(struct Error * this)
{
	free(this);
}

void Error_netHasNoSpaceLeft(char hasSpaceForNode)
{
	if ( ! hasSpaceForNode) {
		fprintf(stderr, "Error_netHasNoSpaceLeft: allocated memory is full.\n");
		exit(1);
	}
}

void Error_netHasNoSuchNode(char hasNode, unsigned int place)
{
	if ( ! hasNode) {
		fprintf(stderr, "Error_netHasNoSuchNode: node %u is missing.\n", place);
		exit(1);
	}
}

