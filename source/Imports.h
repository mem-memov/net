#ifndef IMPORTS_H
#define IMPORTS_H

#include "Import.h"

struct Imports;

struct Imports * Imports_construct();

void Imports_destruct(struct Imports * this);

struct Import * Imports_make(struct Imports * this);

#endif