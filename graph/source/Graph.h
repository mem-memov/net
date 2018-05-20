#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include <stdio.h>

struct Graph;

struct Graph * Graph_construct(size_t size);

void Graph_destruct(struct Graph * this);

char Graph_hasFreePlace(struct Graph * this);

size_t Graph_addNode(struct Graph * this);

void Graph_removeNode(struct Graph * this, size_t place);

void Graph_connectNodes(struct Graph * this, size_t origin, size_t destination);

void Graph_disconnectNodes(struct Graph * this, size_t origin, size_t destination);

void Graph_getNodeDestinations(struct Graph * this, size_t origin, size_t ** destinations, size_t * length);

void Graph_getNodeOrigins(struct Graph * this, size_t destination, size_t ** origins, size_t * length);

char Graph_isNode(struct Graph * this, size_t place);

void Graph_export(struct Graph * this, FILE * file);

void Graph_import(struct Graph * this, FILE * file);

#endif