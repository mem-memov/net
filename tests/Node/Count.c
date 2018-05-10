#include "../../source/Count.h"
#include <stdlib.h>

struct Count
{

};

struct Count * Count_mock()
{
	struct Count * this = malloc(sizeof(struct Count));

	return this;
}

void Count_destruct(struct Count * this)
{
	free(this);
	this = NULL;
}

void Count_bind(struct Count * this, size_t position)
{

}

void Count_create(struct Count * this)
{

}

void Count_delete(struct Count * this)
{

}

void Count_increment(struct Count * this)
{

}

void Count_decrement(struct Count * this)
{

}

char Count_isZero(struct Count * this)
{
	return 0;
}

size_t Count_get(struct Count * this)
{
	return 0;
}