#include "Command.h"
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

struct Command
{
	int count;
	char ** values;
};

struct Command * Command_construct(int count, char ** values)
{
	struct Command * this = malloc(sizeof(struct Command));
	
	this->count = count;
	this->values = values;

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
	
	static int portFlag = 0;
	static int connectionLimitFlag = 0;
	static int bufferLengthFlag = 0;
	static int threadNumberFlag = 0;
	
    int letter;
    int digit_optind = 0;

	while (1) {
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;
		const char * short_options = "p:c:b:t:";
        static struct option long_options[] = {
			{"port", required_argument, &portFlag, 43152},
			{"connection-limit", required_argument, &connectionLimitFlag, 10},
			{"buffer-length", required_argument, &bufferLengthFlag, 8192},
			{"thread-number", required_argument, &threadNumberFlag, 4},
            {NULL, 0, NULL,  0 }
        };

		letter = getopt_long(this->count, this->values, short_options, long_options, &option_index);
		
		if (letter == -1) {
			break;
		}

		switch (letter) {
			case 0:
				/* If this option set a flag, do nothing else now. */
				if (long_options[option_index].flag != 0) {
					break;
				}
				printf ("option %s", long_options[option_index].name);
				if (optarg) {
					printf (" with arg %s", optarg);
				}
				printf ("\n");
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
				/* getopt_long already printed an error message. */
				break;
				
			default:
				printf("unknown flag %d", letter);
				exit(EXIT_FAILURE);
		}

	}
	
	/* Print any remaining command line arguments (not options). */
	if (optind < this->count) {
	printf ("non-option ARGV-elements: ");
		while (optind < this->count) {
			printf ("%s ", this->values[optind++]);
		}
		putchar ('\n');
	}

	
	* port = portFlag;
	* connectionLimit = connectionLimitFlag;
	* bufferLength = bufferLengthFlag;
	* threadNumber = threadNumberFlag;
}