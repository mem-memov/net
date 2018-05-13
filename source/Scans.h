#ifndef SCANS_H
#define SCANS_H

#include "Scan.h"

struct Scans;

struct Scans * Scans_construct();

void Scans_destruct(struct Scans * this);

struct Scan * Scans_make(struct Scans * this);

#endif