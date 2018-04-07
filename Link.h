#ifndef LINK_H
#define LINK_H

struct Link {
	int nodePlace;
	int nextLinkPlace;
};

struct Link * Link_construct(
	int nodePlace,
	int nextLinkPlace
);

void Link_destruct(struct Link * this);

#endif