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

void test_it_accepts_help_structures_to_avoid_eternal_cycle_when_constructing()
{
	size_t places[6] = {1, 2, 3, 4, 5, 6};
	struct Direction * direction = Direction_constructIncoming(places);
	
	struct Direction * nextDirection = Direction_constructIncoming(places);
	Direction_setPool(direction, nextDirection);
	
	assert(direction->nextDirection == nextDirection && "A direction requires a helping set of pointers to operate on the next direction.");
}

void test_it_supplies_its_place_inside_the_storage_array()
{
	size_t places[6] = {1, 2, 3, 4, 5, 6};
	struct Direction * direction = Direction_constructIncoming(places);
	
	size_t place = 0;
	Direction_bind(direction, place);
	
	size_t result = Direction_getPlace(direction);
	
	assert(result == place && "A direction keeps the place it is bound to inside the storage array.");
}

void test_it_writes_values_of_a_fresh_direction_to_the_store()
{
	size_t places[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	struct Direction * direction = Direction_constructIncoming(places);
	
	size_t place = 0;
	size_t destination = 6;
	Direction_create(direction, place, destination);
	
	assert((*direction->node) == destination && "A direction keeps the node it points to.");
	assert((*direction->previous) == 0 && "A new direction is not connected to any previous direction.");
	assert((*direction->next) == 0 && "A new direction is not connected to any following direction.");
}

void test_it_reads_values_of_an_existing_direction_from_the_store()
{
	size_t places[12] = {1, 2, 3, 4, 5, 6};
	struct Direction * direction = Direction_constructIncoming(places);
	
	size_t place = 0;
	Direction_read(direction, place);
	
	assert(direction->place == place && "A direction keeps the place it is bound to inside the storage array.");
	assert((*direction->node) == 4 && "A direction keeps the node it points to.");
	assert((*direction->previous) == 5 && "A direction can be connected to a previous direction.");
	assert((*direction->next) == 6 && "A new direction can be connected to a following direction.");
}

int main(int argc, char** argv)
{
	test_it_contructs_an_outgoing_direction();
	test_it_contructs_an_imcoming_direction();
	test_it_accepts_help_structures_to_avoid_eternal_cycle_when_constructing();
	test_it_supplies_its_place_inside_the_storage_array();
	test_it_writes_values_of_a_fresh_direction_to_the_store();
	test_it_reads_values_of_an_existing_direction_from_the_store();

	return (EXIT_SUCCESS);
}

