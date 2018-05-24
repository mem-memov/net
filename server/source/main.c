#include "Server.h"
#include "Signal.h"
#include "Application.h"
#include "Help.h"
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
	
	struct Help * help = Help_construct();
	
	struct Command * command = Command_construct(argc, argv, help);
	
	Command_getParameters(command, &port, &connectionLimit, &bufferLength, &threadNumber);
	
	Command_destruct(command);

    struct Signal * sigint = Signal_constructSigint(handleShutDown);
    Signal_catch(sigint);

    struct Application * application = Application_construct(bufferLength);

    server = Server_construct(port, connectionLimit, bufferLength, threadNumber, application);

    Help_printStatus(help, port, connectionLimit, bufferLength, threadNumber);
	
	Help_destruct(help);
	
    Server_start(server);

    return(0);
}

