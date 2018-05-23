#include "Server.h"
#include "Signal.h"
#include "Application.h"
#include <stdlib.h>
#include <stdio.h>

struct Server * server = NULL;

void handleShutDown()
{
    if (NULL != server)
    {
        Server_stop(server);
        Server_destruct(server);
    }

    exit(0);
}

void printHelp(int port, int connectionLimit, int bufferLength);

int main(int argc, char *argv[])
{
    struct Signal * sigint = Signal_constructSigint(handleShutDown);
    Signal_catch(sigint);

    int port = 43152;
    if (2 <= argc)
    {
        port = (int)strtol(argv[1], NULL, 10);
    }

    int connectionLimit = 10;
    if (3 <= argc)
    {
        connectionLimit = (int)strtol(argv[2], NULL, 10);
    }

    int bufferLength = 8192;
    if (4 <= argc)
    {
        bufferLength = (int)strtol(argv[3], NULL, 10);
    }
	
	int threadNumber = 4;
    if (5 <= argc)
    {
        threadNumber = (int)strtol(argv[4], NULL, 10);
    }

    struct Application * application = Application_construct(bufferLength);

    server = Server_construct(port, connectionLimit, bufferLength, threadNumber, application);

    printHelp(port, connectionLimit, bufferLength);
    Server_start(server);

    return(0);
}

void printHelp(int port, int connectionLimit, int bufferLength)
{
    printf("Node Database Server is running:\n");
    printf(" port(1): %d.\n", port);
    printf(" maximum connections(2): %d\n", connectionLimit);
    printf(" buffer size(3): %d bytes\n", bufferLength);
    printf("Commands:\n");
    printf(" create\n");
    printf(" read my_id\n");
    printf(" connect my_from_id my_to_id\n");
    printf(" intersect my_id_1 my_id_2 ...\n");
    printf(" union my_id_1 my_id_2 ...\n");
    printf(" difference my_id_1 my_id_2 ...\n");
    printf(" insiders my_container_id my_id_1 my_id_2 ...\n");
    printf(" outsiders my_container_id my_id_1 my_id_2 ...\n");
    printf(" exit\n");
    printf("Source code:");
    printf(" https://github.com/mem-memov/net\n");
    printf("Press Ctrl+C to stop this server.\n");
}
