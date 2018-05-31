#ifndef NETERROR_H
#define NETERROR_H

struct NetError;

struct NetError * NetError_construct();

void NetError_destruct(struct NetError * this);

#endif
