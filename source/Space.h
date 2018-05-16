#ifndef SPACE_H
#define SPACE_H

#include <stdlib.h>
#include <stdio.h>
#include "Net.h"

struct Space;

struct Space * Space_construct(size_t size);

void Space_destruct(struct Space * this);

char Space_hasFreePlace(struct Space * this);

size_t Space_addNode(struct Space * this);

void Space_removeNode(struct Space * this, size_t place);

void Space_connectNodes(struct Space * this, size_t origin, size_t destination);

void Space_disconnectNodes(struct Space * this, size_t origin, size_t destination);

void Space_getNodeTargets(struct Space * this, size_t origin, size_t ** nodes, size_t * length);

void Space_getIncomingNodes(struct Space * this, const size_t * target, size_t * link, size_t * origin);

char Space_isNode(struct Space * this, size_t place);

void Space_export(struct Space * this, FILE * file);

void Space_import(struct Space * this, FILE * file);

#endif