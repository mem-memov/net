#ifndef APPLICATION_HEADER
#define APPLICATION_HEADER

#include "Request.h"
#include "Response.h"

struct Application;

struct Application * Application_construct(int bufferLength);

void Application_destruct(struct Application * this);

void Application_execute(struct Application * this, struct Request * request, struct Response * response);

#endif
