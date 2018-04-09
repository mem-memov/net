#include "Net.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Error.h"
#include "Node.h"

struct Net * Net_construct(unsigned int size, struct Error * error)
{
	struct Net * this = malloc(sizeof(struct Net));
	
	this->size = size;
	this->offset = 0;
	this->nodes = (struct Node **)malloc(sizeof(unsigned int) * this->size);
	this->error = error;

	return this;
}

void Net_destruct(struct Net * this)
{
	free(this->nodes);
	
	free(this);
}

char Net_canAddNode(struct Net * this)
{
	if (this->offset < this->size) {
		return 1;
	}
	
	return 0;
}

struct Node * Net_addNode(struct Net * this)
{
	Error_netHasNoSpaceLeft(Net_canAddNode(this));
	
	struct Node * node = Node_construct(this->offset + 1);
	
	* (this->nodes + this->offset) = node;
	
	this->offset++;
	
	return node;
}

char Net_hasNode(struct Net * this, unsigned int place)
{
	if (this->offset < place) {
		return 0;
	}
	
	return 1;
}

struct Node * Net_getNode(struct Net * this, unsigned int place)
{
	Error_netHasNoSuchNode(Net_hasNode(this, place), place);
	
	return this->nodes[place - 1];
}

void Net_export(struct Net * this, FILE * file)
{
	struct Node * node;
	unsigned int offset = 0;
	
	fprintf(file, "%u\n", this->offset);
	
	while (offset < this->offset) {
		node = Net_getNode(this, offset + 1);
		fprintf(file, "\n");
		Node_export(node, file);
		offset++;
	}
}

void Net_import(struct Net * this, FILE * file)
{
	unsigned int total;
	
	fscanf(file, "%u\n", &total);
	
	fprintf(stdout, "%u\n", total);
	
	struct Node * node;
	
	do {
		node = Net_addNode(this);
	} while(Node_getPlace(node) < total);
	
	unsigned int originPlace;
	unsigned int destinationPlace;
	struct Node * originNode;
	struct Node * destinationNode;
	
	unsigned int index;
	
	unsigned int place;
	unsigned int count;
	
	for (originPlace = 1; originPlace <= total; originPlace++) {
		originNode = Net_getNode(this, originPlace);
		fscanf(file, "%u\n", &place);
		fscanf(file, "%u\n", &count);
		for (index = 0; index < count; index++) {
			fscanf(file, "%u\n", &destinationPlace);
			destinationNode = Net_getNode(this, destinationPlace);
			Node_connect(originNode, destinationNode);
		}
		fscanf(file, "\n");
	}
}