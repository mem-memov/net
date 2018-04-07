#ifndef LINK_H
#define LINK_H

struct Link {
	unsigned int nodePlace;
	unsigned int nextLinkPlace;
};

struct Link * Link_construct(
	unsigned int nodePlace,
	unsigned int nextLinkPlace
);

void Link_destruct(struct Link * this);

unsigned int Link_getNodePlace(struct Link * this);

void Link_appendNode(struct Link * this, unsigned int nodePlace);

#endif