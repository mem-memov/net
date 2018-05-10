#ifndef NODES_H
#define NODES_H

#include "Counts.h"
#include "Links.h"
#include "Node.h"
#include "NodeError.h"
#include "Places.h"

struct Nodes;

struct Nodes * Nodes_construct(
	struct Places * places, 
	struct Counts * counts, 
	struct Links * links, 
	struct NodeError * nodeError
);

void Nodes_destruct(struct Nodes * this);

struct Node * Nodes_make(struct Nodes * this);

#endif 

