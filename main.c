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
	char filePath[300];
	FILE * file;

	while (1) {
		printf("Enter a command: ");
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
			
			printf("origin node:");
			scanf("%u", &origin);
			
			if ( ! Space_isNode(space, origin)) {
				printf("%u is not a node\n", origin);
				continue;
			}

			printf("destination node:");
			scanf("%u", &destination);
			
			if ( ! Space_isNode(space, destination)) {
				printf("%u is not a node\n", destination);
				continue;
			}

			Space_connectNodes(space, origin, destination);
			
			continue;
		}

		if (strcmp("read", command) == 0 || strcmp(":", command) == 0) {
			
			printf("node: ");
			scanf("%u", &place);

			if ( ! Space_isNode(space, place)) {
				printf("%u is not a node\n", place);
				continue;
			}
			
			next = place;
			while (0 != next) {
				next = Space_getNode(space, next, &place);
				printf("%u\n", place);
			} 
			
			continue;
		}

		if (strcmp("export", command) == 0 || strcmp(">>", command) == 0) {

			printf( "target file path:");
			scanf("%s", filePath);

			file = fopen(filePath, "wb");
			Space_export(space, file);
			fclose(file);
			
			continue;
		}

		if (strcmp("import", command) == 0 || strcmp("<<", command) == 0) {

			printf( "source file path:");
			scanf("%s", filePath);

			file = fopen(filePath, "rb");
			Space_import(space, file);
			fclose(file);
			
			continue;
		}

		if (strcmp("exit", command) == 0 || strcmp("q", command) == 0) {
			break;
		}
		
		printf( "Unknown command '%s'. Enter 'exit' to stop execution.\n", command);
   }

   return (EXIT_SUCCESS);
}

