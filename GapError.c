#include "GapError.h"
#include <stdlib.h>

void GapError_placeCanBeReadOnlyOnce(size_t place)
{
	if (0 == place) {
		exit(1);
	}
}

