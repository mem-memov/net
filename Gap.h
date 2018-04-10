#ifndef GAP_H
#define GAP_H

struct Gap {
	unsigned int place;
	struct Gap * next;
};

struct Gap * Gap_construct(unsigned int place, struct Gap * next);

void Gap_destruct(struct Gap * this);

unsigned int Gap_getPlace(struct Gap * this);

struct Gap * Gap_getNext(struct Gap * this);

#endif