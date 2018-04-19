#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../source/Direction.c"

void test_it_contructs_an_outgoing_direction()
{
	size_t places[6] = {1, 2, 3, 4, 5, 6};
	struct Direction * direction = Direction_constructOutgoing(places);
	
	assert(direction->places == places && "A direction can access data in this store.");
	assert(direction->offset == 0 && "An outgoing direction starts at the beginning of an entry.");
	assert(direction->nextDirection == NULL && "A new direction is not connected to any other direction.");
}

void test_it_contructs_an_imcoming_direction()
{
	size_t places[6] = {1, 2, 3, 4, 5, 6};
	struct Direction * direction = Direction_constructIncoming(places);
	
	assert(direction->places == places && "A direction can access data in this store.");
	assert(direction->offset == 3 && "An incoming direction starts right after the outgoing direction.");
	assert(direction->nextDirection == NULL && "A new direction is not connected to any other direction.");
}

int main(int argc, char** argv)
{
	test_it_contructs_an_outgoing_direction();
	test_it_contructs_an_imcoming_direction();

	return (EXIT_SUCCESS);
}

