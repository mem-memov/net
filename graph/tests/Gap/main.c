#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../source/Gap.c"
#include "../Place.c"

struct Gap * gap;
struct Place * zero;
struct Place * count;
struct Place * next;
struct Place * three;
struct Place * four;
struct Place * five;

void prepareTest()
{
	zero = Place_mock();
	count = Place_mock();
	next = Place_mock();
	three = Place_mock();
	four = Place_mock();
	five = Place_mock();
	
	gap = Gap_construct(zero, count, next, three, four, five);
}

void demolishTest()
{
	Gap_destruct(gap);
}

void it_writes_new_gap_to_store()
{
	prepareTest();
	
	size_t place = 24;
	size_t nextGapPlace = 60;
	size_t countValue = 11;
	
	Gap_create(gap, place, nextGapPlace, countValue);
	
	assert(
		0 == strcmp(zero->method[0], "Place_bind") 
		&& zero->position[0] == 24
	);
	assert(
		0 == strcmp(count->method[0], "Place_bind") 
		&& count->position[0] == 25
	);
	assert(
		0 == strcmp(next->method[0], "Place_bind") 
		&& next->position[0] == 26
	);
	assert(
		0 == strcmp(three->method[0], "Place_bind") 
		&& three->position[0] == 27
	);
	assert(
		0 == strcmp(four->method[0], "Place_bind") 
		&& four->position[0] == 28
	);
	assert(
		0 == strcmp(five->method[0], "Place_bind") 
		&& five->position[0] == 29
	);
	
	assert(
		0 == strcmp(zero->method[1], "Place_set") 
		&& zero->value[1] == 0
	);
	assert(
		0 == strcmp(count->method[1], "Place_set") 
		&& count->value[1] == countValue
	);
	assert(
		0 == strcmp(next->method[1], "Place_set") 
		&& next->value[1] == nextGapPlace
	);
	assert(
		0 == strcmp(three->method[1], "Place_set") 
		&& three->value[1] == 0
	);
	assert(
		0 == strcmp(four->method[1], "Place_set") 
		&& four->value[1] == 0
	);
	assert(
		0 == strcmp(five->method[1], "Place_set") 
		&& five->value[1] == 0
	);
	
	demolishTest();
}

void it_reads_gap_fields_from_store()
{
	prepareTest();
	
	size_t place = 24;
	
	Gap_read(gap, place);
	
	assert(
		0 == strcmp(zero->method[0], "Place_bind") 
		&& zero->position[0] == 24
	);
	assert(
		0 == strcmp(count->method[0], "Place_bind") 
		&& count->position[0] == 25
	);
	assert(
		0 == strcmp(next->method[0], "Place_bind") 
		&& next->position[0] == 26
	);
	assert(
		0 == strcmp(three->method[0], "Place_bind") 
		&& three->position[0] == 27
	);
	assert(
		0 == strcmp(four->method[0], "Place_bind") 
		&& four->position[0] == 28
	);
	assert(
		0 == strcmp(five->method[0], "Place_bind") 
		&& five->position[0] == 29
	);
	
	demolishTest();
}

void it_erases_gap_from_store()
{
	prepareTest();
	
	Gap_delete(gap);
	
	assert(
		0 == strcmp(zero->method[0], "Place_set") 
		&& zero->value[0] == 0
	);
	assert(
		0 == strcmp(count->method[0], "Place_set") 
		&& count->value[0] == 0
	);
	assert(
		0 == strcmp(next->method[0], "Place_set") 
		&& next->value[0] == 0
	);
	assert(
		0 == strcmp(three->method[0], "Place_set") 
		&& three->value[0] == 0
	);
	assert(
		0 == strcmp(four->method[0], "Place_set") 
		&& four->value[0] == 0
	);
	assert(
		0 == strcmp(five->method[0], "Place_set") 
		&& five->value[0] == 0
	);
	
	demolishTest();
}

void it_supplies_next_gap_number()
{
	prepareTest();
	
	count->value[0] = 11;
	
	size_t result = Gap_increment(gap);
	
	assert(0 == strcmp(count->method[0], "Place_get"));
	
	assert(result == 12);
	
	demolishTest();
}

void it_supplies_next_gap_place()
{
	prepareTest();
	
	next->value[0] = 120;
	
	size_t result = Gap_getNext(gap);
	
	assert(0 == strcmp(next->method[0], "Place_get"));
	
	assert(result == 120);
	
	demolishTest();
}

int main(int argc, char** argv)
{
	it_writes_new_gap_to_store();
	it_reads_gap_fields_from_store();
	it_erases_gap_from_store();
	it_supplies_next_gap_number();
	it_supplies_next_gap_place();

	return (EXIT_SUCCESS);
}