#ifndef IMPORT_H
#define IMPORT_H

#include <stdio.h>

struct Import;

struct Import * Import_construct();

void Import_destruct(struct Import * this);

void Import_read(struct Import * this, FILE * file);

#endif