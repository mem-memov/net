#ifndef SERVER_HEADER
#define SERVER_HEADER

#include "Application.h"

struct Server;

struct Server * Server_construct(
    int port, 
    int connectionLimit, 
    int bufferLength, 
    int threadNumber,
    struct Application * application
);

void Server_destruct(struct Server * this);

void Server_start(struct Server * this);

void Server_stop(struct Server * this);

#endif
