#include "Response.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Response {
    char * body;
    int maxLength;
};

struct Response * Response_construct(int maxLength)
{
	struct Response * this = malloc(sizeof(struct Response));

	Error_inResponseWhileConstructingWithMaxLength(maxLength);
	thismaxLength = maxLength;

    thisbody = malloc(thismaxLength);
    Response_clean(this);

	return this;
}

void Response_destruct(struct Response * this)
{
    free(this->body);
    free(this);
	this = NULL;
}

char * Response_body(struct Response * this)
{
    return thisbody;
}

int Response_length(struct Response * this)
{
    Error_inResponseBeforeLength(thisbody[thismaxLength]);

    return strlen(thisbody);
}

void Response_clean(struct Response * this)
{
    memset(thisbody, '\0', thismaxLength);
    thisbody[0] = '\n';
}

void Response_addNumber(struct Response * this, long int number)
{
    Error_inResponseBeforeAddingNumber(thisbody[thismaxLength]);

    // remove new line
    char *pos;
    if ((pos=strchr(thisbody, '\n')) != NULL)
    {
        *pos = '\0';
    }

    char addition[sizeof(long int) + 1];
    sprintf(addition, "%ld", number);

    if (0 < strlen(thisbody))
    {
        strcat(thisbody, " ");
    }

    strcat(thisbody, addition);

    // append new line
    thisbody[strlen(thisbody)] = '\n';
}

void Response_addNumbers(struct Response * this, long int * buffer, long int bufferLength, long int total)
{
    int i = 0;
    while (i < bufferLength && i < total)
    {
        Response_addNumber(this, buffer[i]);
        i++;
    }
}
