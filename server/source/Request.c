#include "Request.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Error.h"

struct Request {
    char * body;
    int maxLength;
};

struct Request * Request_construct(int maxLength)
{
	struct Request * this = malloc(sizeof(struct Request));

    Error_inRequestWhileConstructingWithMaxLength(maxLength);
    this->maxLength = maxLength;

    this->body = malloc(this->maxLength);
    Request_clean(this);

	return this;
}

void Request_destruct(struct Request * this)
{
    free(this->body);
    free(this);
}

char * Request_body(struct Request * this)
{
    return this->body;
}

int Request_maxLength(struct Request * this)
{
    return this->maxLength;
}

void Request_clean(struct Request * this)
{
    memset(this->body, '\0', this->maxLength);
}

char Request_isFinished(struct Request * this)
{
    Error_inRequestBeforeFinishedCheck(this->body[this->maxLength]);

    char lastCharacter = this->body[strlen(this->body) - 1];

    if ('\n' == lastCharacter)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

char Request_isCommand(struct Request * this, char * command)
{
    Error_inRequestBeforeCommandCheck(this->body[this->maxLength]);

    if (strstr(this->body, command) == this->body)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

long int Request_getArgument(struct Request * this, int orderNumber)
{
    Error_inRequestBeforeGettingArgument(this->body[this->maxLength]);

    int wordCount = 0;
    char character;
    int requestLength = strlen(this->body) + 1;
    int argumentLength = sizeof(long int) + 1;
    char argument[argumentLength];
    char isFound = 0;
    char argumentIndex = 0;
    int i;

    for (i = 0; i < requestLength; i++)
    {
        character = this->body[i];

        if (' ' == character)
        {
            if (wordCount == orderNumber)
            {
                break;
            }

            wordCount++;
            argumentIndex = 0;
            memset(argument, '\0', argumentLength);
        }
        else
        {
            if (wordCount == orderNumber)
            {
                isFound = 1;
                argument[argumentIndex] = character;
                argument[argumentIndex + 1] = '\0';
                argumentIndex++;

                if ((argumentLength - 2) == argumentIndex)
                {
                    break;
                }
            }
        }
    }

    Error_inRequestAfterGettingArgument(isFound, orderNumber);

    return strtol(argument, NULL, 10);
}

long int Request_countArguments(struct Request * this)
{
    Error_inRequestBeforeGettingArgument(this->body[this->maxLength]);

    int count = 0;
    char character;
    int requestLength = strlen(this->body) + 1;
    int i;
    for (i = 0; i < requestLength; i++)
    {
        character = this->body[i];

        if (' ' == character)
        {
            count++;
        }
    }

    return count;
}

void Request_getArguments(struct Request * this, long int * arguments, long int length)
{
    Error_inRequestBeforeGettingArguments(this->body[this->maxLength]);

    long int n;
    for (n = 0; n < length; n++)
    {
        arguments[n] = Request_getArgument(this, n+1);
    }
}

char Request_isEmpty(struct Request * this)
{
    if ('\0' == this->body[0])
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
