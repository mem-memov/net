#ifndef SCAN_H
#define SCAN_H

#include <stdlib.h>

struct Scan;

struct Scan * Scan_construct();

void Scan_destruct(struct Scan * this);

size_t Scan_findGaps(struct Scan * this);

#endif