#ifndef FACTORY_H
#define FACTORY_H

#include "Boat.h"
#include "Import.h"
#include "Link.h"
#include "Node.h"

struct Factory;

struct Factory * Factory_construct(
	unsigned char * bytes, 
	size_t graphSize, 
	size_t entrySize, 
	size_t placeSize
);

void Factory_destruct(struct Factory * this);

struct Boat * Factory_makeBoat(struct Factory * this);

struct Import * Factory_makeImport(struct Factory * this);

struct Link * Factory_makeLink(struct Factory * this);

struct Node * Factory_makeNode(struct Factory * this);

#endif