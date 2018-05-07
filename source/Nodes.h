#ifndef NODES_H
#define NODES_H

#include "Node.h"

struct Nodes;

struct Nodes * Nodes_construct();

void Nodes_destruct(struct Nodes * this);

struct Node * Nodes_make(struct Nodes * this);

#endif 

