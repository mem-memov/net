#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../source/Count.c"
#include "../CountError.c"
#include "../Place.c"

struct Count * count;
struct CountError * error;
struct Place * place;

void prepareTest()
{
	place = Place_mock();
	error = CountError_mock();
	
	count = Count_construct(place, error);
}

void demolishTest()
{
	Count_destruct(count);
	CountError_destruct(error);
}

void it_gets_bound_to_a_position_in_store()
{
	prepareTest();
	
	Count_bind(count, 30);
	
	assert(
		0 == strcmp(place->method[0], "Place_bind") 
		&& place->position[0] == 30
	);
	
	demolishTest();
}

void it_writes_new_count_to_store()
{
	prepareTest();
	
	Count_create(count);
	
	assert(
		0 == strcmp(place->method[0], "Place_set") 
		&& place->value[0] == 0
	);
	
	demolishTest();
}

void it_deletes_existing_count_from_store()
{
	prepareTest();
	
	Count_delete(count);
	
	assert(
		0 == strcmp(place->method[0], "Place_set") 
		&& place->value[0] == 0
	);
	
	demolishTest();
}

int main(int argc, char** argv)
{
	it_gets_bound_to_a_position_in_store();
	it_writes_new_count_to_store();
	it_deletes_existing_count_from_store();

	return (EXIT_SUCCESS);
}