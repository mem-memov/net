#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../source/Gap.c"
#include "GapError.c"

void it_contructs_a_tail_gap()
{
	struct GapError * error = GapError_mock();
	
	size_t place = 6;
	struct Gap * gap = Gap_construct(place, NULL, error);

	assert(gap->place == place && "A tail gap specifies the beginning of an unused entry.");
	assert(gap->next == NULL && "A tail gap is not connected to any other gap.");
	
	Gap_destruct(gap);
	GapError_destruct(error);
}

void it_contructs_a_head_gap()
{
	struct GapError * error = GapError_mock();
	size_t place = 6;
	struct Gap * next = Gap_construct(place, NULL, error);
	struct Gap * gap = Gap_construct(place, next, error);
	
	assert(gap->place == place && "A head gap specifies the beginning of an unused entry.");
	assert(gap->next == next && "A head gap is connected to some other gap.");
	
	Gap_destruct(next);
	Gap_destruct(gap);
	GapError_destruct(error);
}

void it_supplies_entry_place()
{
	struct GapError * error = GapError_mock();
	size_t place = 6;
	struct Gap * gap = Gap_construct(place, NULL, error);
	
	size_t result = Gap_getPlace(gap);
	
	assert(result == place && "A gap supplies the beginning of an unused entry.");
	assert(gap->place == 0 && "A gap can supply only once. It gets erased after the first use.");
	
	Gap_destruct(gap);
	GapError_destruct(error);
}

void it_checks_entry_place_is_invalid()
{
	struct GapError * error = GapError_mock();
	error->method = "";
	error->place = 0;

	size_t place = 555;
	struct Gap * gap = Gap_construct(place, NULL, error);
	
	assert(0 == strcmp(error->method, "GapError_zeroPlaceIsReservedForInvalidGap"));
	assert(place == error->place && "GapError_zeroPlaceIsReservedForInvalidGap place");
	
	Gap_destruct(gap);
	GapError_destruct(error);
}

int main(int argc, char** argv)
{
	it_contructs_a_tail_gap();
	it_contructs_a_head_gap();
	it_supplies_entry_place();
	it_checks_entry_place_is_invalid();

	return (EXIT_SUCCESS);
}

