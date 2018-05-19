#ifndef CONNECTION_HEADER
#define CONNECTION_HEADER

#include "Request.h"
#include "Response.h"

struct Connection;

struct Connection * Connection_construct(int descriptor, struct Request * request, struct Response * response);

void Connection_destruct(struct Connection * this);

struct Request * Connection_request(struct Connection * this);

struct Response * Connection_response(struct Connection * this);

void Connection_close(struct Connection * this);

void Connection_receive(struct Connection * this);

void Connection_send(struct Connection * this);

char Connection_mustClose(struct Connection * this);

char Connection_isIdle(struct Connection * this);

#endif
