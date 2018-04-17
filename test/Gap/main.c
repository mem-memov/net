#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../Gap.h"

void test_it_contructs_a_tail_gap()
{
	size_t place = 6;
	struct Gap * gap = Gap_construct(place, NULL);
	
	assert(gap->place == place && "A tail gap specifies the beginning of an unused entry.");
	assert(gap->next == NULL && "A tail gap is not connected to any other gap.");
}

void test_it_contructs_a_head_gap()
{
	size_t place = 6;
	struct Gap * next = Gap_construct(place, NULL);
	struct Gap * gap = Gap_construct(place, next);
	
	assert(gap->place == place && "A head gap specifies the beginning of an unused entry.");
	assert(gap->next == next && "A head gap is connected to some other gap.");
}

void test_it_supplies_entry_place()
{
	size_t place = 6;
	struct Gap * gap = Gap_construct(place, NULL);
	
	size_t result = Gap_getPlace(gap);
	
	assert(result == place && "A gap supplies the beginning of an unused entry.");
	assert(gap->place == 0 && "A gap can supply only once.");
}

int main(int argc, char** argv) {

	test_it_contructs_a_tail_gap();
	test_it_contructs_a_head_gap();
	test_it_supplies_entry_place();

	return (EXIT_SUCCESS);
}

