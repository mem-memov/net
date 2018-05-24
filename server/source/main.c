#include "Server.h"
#include "Signal.h"
#include "Application.h"
#include "Command.h"
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

void printHelp(int port, int connectionLimit, int bufferLength, int threadNumber);

int main(int argc, char *argv[])
{
	int port;
	int connectionLimit;
	int bufferLength;
	int threadNumber;
	
	struct Command * command = Command_construct(argc, argv);
	
	Command_getParameters(command, &port, &connectionLimit, &bufferLength, &threadNumber);
	
	Command_destruct(command);

    struct Signal * sigint = Signal_constructSigint(handleShutDown);
    Signal_catch(sigint);

    struct Application * application = Application_construct(bufferLength);

    server = Server_construct(port, connectionLimit, bufferLength, threadNumber, application);

    printHelp(port, connectionLimit, bufferLength, threadNumber);
    Server_start(server);

    return(0);
}

void printHelp(int port, int connectionLimit, int bufferLength, int threadNumber)
{
    printf("Node Database Server is running:\n");
    printf(" port: %d.\n", port);
    printf(" maximum connections: %d\n", connectionLimit);
    printf(" buffer size: %d bytes\n", bufferLength);
    printf(" thread number: %d\n", threadNumber);
    printf("Commands:\n");
    printf(" exit\n");
    printf("Source code:");
    printf(" https://github.com/mem-memov/net\n");
    printf("Press Ctrl+C to stop this server.\n");
}
