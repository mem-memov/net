#include "Response.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Error.h"

struct Response {
    char * body;
    int maxLength;
};

struct Response * Response_construct(int maxLength)
{
	struct Response * this = malloc(sizeof(struct Response));

	Error_inResponseWhileConstructingWithMaxLength(maxLength);
	this->maxLength = maxLength;

    this->body = malloc(this->maxLength);
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
    return this->body;
}

int Response_length(struct Response * this)
{
    Error_inResponseBeforeLength(this->body[this->maxLength]);

    return strlen(this->body);
}

void Response_clean(struct Response * this)
{
    memset(this->body, '\0', this->maxLength);
    this->body[0] = '\n';
}

void Response_addNumber(struct Response * this, long int number)
{
    Error_inResponseBeforeAddingNumber(this->body[this->maxLength]);

    // remove new line
    char *pos;
    if ((pos=strchr(this->body, '\n')) != NULL)
    {
        *pos = '\0';
    }

    char addition[sizeof(long int) + 1];
    sprintf(addition, "%ld", number);

    if (0 < strlen(this->body))
    {
        strcat(this->body, " ");
    }

    strcat(this->body, addition);

    // append new line
    this->body[strlen(this->body)] = '\n';
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
