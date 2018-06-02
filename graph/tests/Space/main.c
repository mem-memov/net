#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../source/Space.c"
#include "../Place.c"

struct Space * space;
size_t graphSize;
size_t entrySize;
size_t placeSize;

void prepareTest()
{
	graphSize = 1200;
	entrySize = 6;
	placeSize = 4;
	
	space = Space_construct(graphSize, entrySize, placeSize);
}

void demolishTest()
{
	Space_destruct(space);
}

void it_confirms_having_free_space_if_next_entry_below_limit()
{
	prepareTest();
	
	char result = Space_canTakeAnotherEntry(space, 1176, 0);
	
	assert(result == 1);
	
	demolishTest();
}

void it_confirms_having_free_space_if_some_gaps_available()
{
	prepareTest();
	
	char result = Space_canTakeAnotherEntry(space, 1200, 1);
	
	assert(result == 1);
	
	demolishTest();
}

void it_denies_having_free_space()
{
	prepareTest();
	
	char result = Space_canTakeAnotherEntry(space, 1200, 0);
	
	assert(result == 0);
	
	demolishTest();
}

int main(int argc, char** argv)
{
	it_confirms_having_free_space_if_next_entry_below_limit();
	it_confirms_having_free_space_if_some_gaps_available();
	it_denies_having_free_space();

	return (EXIT_SUCCESS);
}