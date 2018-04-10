#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Space.h"


int main(int argc, char** argv) {

	struct Space * space = Space_construct(100);

	char command[100];
	unsigned int place;
	unsigned int origin;
	unsigned int destination;
	unsigned int next;
//	char filePath[300];
//	FILE * file;

	while (1) {
		printf( "Enter a command:");
		scanf("%s", command);
		
		if (strcmp("create", command) == 0 || strcmp("*", command) == 0) {

			if ( ! Space_hasFreePlace(space)) {
				printf("No space for new nodes.\n");
			} else {
				place = Space_addNode(space);
				printf("Node created: %u\n", place);
			}

			continue;
		}

		if (strcmp("connect", command) == 0 || strcmp("+", command) == 0) {
			
			printf( "origin node:");
			scanf("%u", &origin);

			printf( "destination node:");
			scanf("%u", &destination);

			Space_connectNodes(space, origin, destination);
			
			continue;
		}

		if (strcmp("read", command) == 0 || strcmp(":", command) == 0) {
			
			printf( "node:");
			scanf("%u", &place);
			
			do {
				next = Space_getNode(space, &place);
				printf("%u\n", place);
			} while (0 != next);
			
			continue;
		}

//		if (strcmp("export", command) == 0 || strcmp(">>", command) == 0) {
//
//			printf( "target file path:");
//			scanf("%s", filePath);
//
//			file = fopen(filePath, "w+");
//			Net_export(net, file);
//			fclose(file);
//			
//			continue;
//		}
//
//		if (strcmp("import", command) == 0 || strcmp("<<", command) == 0) {
//
//			printf( "source file path:");
//			scanf("%s", filePath);
//
//			file = fopen(filePath, "r");
//			Net_import(net, file);
//			fclose(file);
//			
//			continue;
//		}
//
//		if (strcmp("show", command) == 0 || strcmp(">", command) == 0) {
//
//			Net_export(net, stdout);
//			
//			continue;
//		}

		if (strcmp("exit", command) == 0 || strcmp("q", command) == 0) {
			break;
		}
		
		printf( "Unknown command '%s'. Enter 'exit' to stop execution.\n", command);
   }

   return (EXIT_SUCCESS);
}

