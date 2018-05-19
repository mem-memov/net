#ifndef LISTENER_HEADER
#define LISTENER_HEADER

#include "Connection.h"

struct Listener;

struct Listener * Listener_construct(int port, int connectionLimit);

void Listener_destruct(struct Listener * this);

void Listener_open(struct Listener * this);

void Listener_bind(struct Listener * this);

void Listener_listen(struct Listener * this);

struct Connection * Listener_accept(struct Listener * this, int bufferLength);

void Listener_close(struct Listener * this);

#endif
