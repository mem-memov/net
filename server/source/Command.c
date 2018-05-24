#include "Command.h"
#include <stdlib.h>
#include <getopt.h>

struct Command
{
	int count;
	char ** values;
	struct Help * help;
};

struct Command * Command_construct(int count, char ** values, struct Help * help)
{
	struct Command * this = malloc(sizeof(struct Command));
	
	this->count = count;
	this->values = values;
	this->help = help;

	return this;
}

void Command_destruct(struct Command * this)
{
	free(this);
	this = NULL;
}

void Command_getParameters(
	struct Command * this, 
	int * port,
	int * connectionLimit,
	int * bufferLength,
	int * threadNumber
) {
	const char * short_options = "p:c:b:t:";
	static struct option long_options[] = {
		{"port", required_argument, NULL, 'p'},
		{"connections", required_argument, NULL, 'c'},
		{"buffer", required_argument, NULL, 'b'},
		{"threads", required_argument, NULL, 't'},
		{NULL, 0, NULL,  0 }
	};
	
	int letter;

	while (1) {

		letter = getopt_long(this->count, this->values, short_options, long_options, NULL);
		
		if (letter == -1) {
			break;
		}

		switch (letter) {
			case 0:
				// long option filled
				break;

			case 'p' : 
				* port = (int)strtol(optarg, NULL, 10);
				break;
			case 'c' : 
				* connectionLimit = (int)strtol(optarg, NULL, 10);
				break;
			case 'b' : 
				* bufferLength = (int)strtol(optarg, NULL, 10);
				break;
			case 't' : 
				* threadNumber = (int)strtol(optarg, NULL, 10);
				break;
				
				
			case '?':
				// getopt_long already printed an error message.
				break;
				
			default:
				Help_printCommandLineManual(this->help);
				exit(EXIT_FAILURE);
		}

	}
}