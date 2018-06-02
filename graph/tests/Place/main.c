#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../source/Place.c"

struct Place * place;
unsigned char length;
unsigned char * bytes;

void prepareTest()
{
	length = 4;
	
	bytes = malloc(10 * 6 * length);
	
	place = Place_construct(length, bytes);
}

void demolishTest()
{
	Place_destruct(place);
	free(bytes);
	bytes = NULL;
}

void it_keeps_a_value()
{
	prepareTest();
	
	Place_bind(place, 3);
	
	Place_set(place, 70000);
	
	size_t result = Place_get(place);
	
	assert(result == 70000);
	
	demolishTest();
}

int main(int argc, char** argv)
{
	it_keeps_a_value();

	return (EXIT_SUCCESS);
}