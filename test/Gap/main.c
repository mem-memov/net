#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../source/Gap.c"
#include "GapError.c"

void test_it_contructs_a_tail_gap()
{
	struct GapError * error = GapError_construct();
	size_t place = 6;
	struct Gap * gap = Gap_construct(place, NULL, error);
	
	assert(gap->place == place && "A tail gap specifies the beginning of an unused entry.");
	assert(gap->next == NULL && "A tail gap is not connected to any other gap.");
}

void test_it_contructs_a_head_gap()
{
	struct GapError * error = GapError_construct();
	size_t place = 6;
	struct Gap * next = Gap_construct(place, NULL, error);
	struct Gap * gap = Gap_construct(place, next, error);
	
	assert(gap->place == place && "A head gap specifies the beginning of an unused entry.");
	assert(gap->next == next && "A head gap is connected to some other gap.");
}

void test_it_supplies_entry_place()
{
	struct GapError * error = GapError_construct();
	size_t place = 6;
	struct Gap * gap = Gap_construct(place, NULL, error);
	
	size_t result = Gap_getPlace(gap);
	
	assert(result == place && "A gap supplies the beginning of an unused entry.");
	assert(gap->place == 0 && "A gap can supply only once. It gets erased after the first use.");
}

void test_it_checks_entry_place_is_invalid()
{
	struct GapError * error = GapError_construct();
	error->method = "";
	error->place = 777;

	struct Gap * gap = Gap_construct(0, NULL, error);
	
	assert(0 == strcmp(error->method, "GapError_zeroPlaceIsReservedForInvalidGap"));
	assert(0 == error->place && "GapError_zeroPlaceIsReservedForInvalidGap place");
}

int main(int argc, char** argv)
{
	test_it_contructs_a_tail_gap();
	test_it_contructs_a_head_gap();
	test_it_supplies_entry_place();
	test_it_checks_entry_place_is_invalid();

	return (EXIT_SUCCESS);
}

