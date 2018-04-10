#ifndef SPACE_H
#define SPACE_H

struct Space {
	unsigned int size;
	unsigned int * places;
	unsigned int next;
	struct Gap * gap;
};

struct Space * Space_construct(unsigned int size);

void Space_destruct(struct Space * this);

char Space_hasFreePlace(struct Space * this);

unsigned int Space_addNode(struct Space * this);

void Space_removeNode(struct Space * this, unsigned int place);

void Space_connectNodes(struct Space * this, unsigned int origin, unsigned int destination);

void Space_disconnectNodes(struct Space * this, unsigned int origin, unsigned int destination);

unsigned int Space_getNode(struct Space * this, unsigned int * place);

char Space_isNode(struct Space * this, unsigned int place);

#endif