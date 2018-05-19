#include "Error.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void Error_inApplicationWhileExecutingWithSmallBuffer(int bufferLength, long int total)
{
    if (bufferLength < total)
    {
        fprintf(stderr, "Error_inApplicationWhileExecutingWithSmallBuffer: buffer size %d is less than %ld.\n", bufferLength, total);
        exit(1);
    }
}

void Error_inApplicationWhileExecutingWithUnknownCommand()
{
    fprintf(stderr, "Error_inApplicationWhileExecutingWithUnknownCommand: command not known.\n");
    exit(1);
}

void Error_inApplicationWhileExecutingWithFewArguments(long int actual, char minimum)
{
    if (actual < minimum)
    {
        fprintf(stderr, "Error_inApplicationWhileExecutingWithFewArguments: minimum %c, given %ld.\n", minimum, actual);
        exit(1);
    }
}

void Error_inConnectionWhileReceiving(int availableBufferLength)
{
    if (0 > availableBufferLength)
    {
        fprintf(stderr, "Error_inConnectionWhileReceiving: available buffer length: %d.\n", availableBufferLength);
        exit(1);
    }
}

void Error_inConnectionAfterSending(int sendResult)
{
    if (-1 == sendResult)
    {
        fprintf(stderr, "Error_inConnectionAfterSending.\n");
        exit(1);
    }
}

void Error_inListenerBeforeOpeningSocket(int listenerDescriptor)
{
    if (0 <= listenerDescriptor)
    {
        fprintf(stderr, " Error_inListenerBeforeOpeningSocket.\n");
        exit(1);
    }
}

void Error_inListenerAfterOpeningSocket(int listenerDescriptor)
{
    if (-1 == listenerDescriptor)
    {
        fprintf(stderr, "Error_inListenerAfterOpeningSocket.\n");
        exit(1);
    }
}

void Error_inListenerBeforeBindingToPort(int listenerDescriptor)
{
    if (0 > listenerDescriptor)
    {
        fprintf(stderr, "Error_inListenerBeforeBindingToPort.\n");
        exit(1);
    }
}

void Error_inListenerAfterSettingSocketOption(int setSocketOptionResult)
{
    if (-1 == setSocketOptionResult)
    {
        fprintf(stderr, "Error_inListenerAfterSettingSocketOption.\n");
        exit(1);
    }
}

void Error_inListenerAfterBindingToPort(int bindResult)
{
    if (-1 == bindResult)
    {
        fprintf(stderr, "Error_inListenerAfterBindingToPort.\n");
        exit(1);
    }
}

void Error_inListenerBeforeListening(int listenerDescriptor)
{
    if (0 > listenerDescriptor)
    {
        fprintf(stderr, "Error_inListenerBeforeListening.\n");
        exit(1);
    }
}

void Error_inListenerAfterListening(int listenResult)
{
    if (-1 == listenResult)
    {
        fprintf(stderr, "Error_inListenerAfterListening.\n");
        exit(1);
    }
}

void Error_inListenerBeforeAcceptingConnection(int listenerDescriptor)
{
    if (0 > listenerDescriptor)
    {
        fprintf(stderr, "Error_inListenerBeforeAcceptingConnection.\n");
        exit(1);
    }
}

void Error_inListenerAfterAcceptingConnection(int connectionDescriptor)
{
    if (-1 == connectionDescriptor)
    {
        fprintf(stderr, "Error_inListenerAfterAcceptingConnection.\n");
        exit(1);
    }
}

void Error_inRequestWhileConstructingWithMaxLength(int maxLength)
{
    if (maxLength < 2)
    {
        fprintf(stderr, "Error_inRequestWhileConstructingWithMaxLength: maximum request length %d is too small.\n", maxLength);
        exit(1);
    }
}

void Error_inRequestBeforeFinishedCheck(char endCharacter)
{
    if ('\0' != endCharacter)
    {
        fprintf(stderr, "Error_inRequestBeforeFinishedCheck: request body overflow.\n");
        exit(1);
    }
}

void Error_inRequestBeforeCommandCheck(char endCharacter)
{
    if ('\0' != endCharacter)
    {
        fprintf(stderr, "Error_inRequestBeforeCommandCheck: request body overflow.\n");
        exit(1);
    }
}

void Error_inRequestBeforeGettingArgument(char endCharacter)
{
    if ('\0' != endCharacter)
    {
        fprintf(stderr, "Error_inRequestBeforeGettingArgument: request body overflow.\n");
        exit(1);
    }
}

void Error_inRequestAfterGettingArgument(char isFound, int orderNumber)
{
    if (0 == isFound)
    {
        fprintf(stderr, "Error_inRequestAfterGettingArgument: argument %d not found.\n", orderNumber);
        exit(1);
    }
}

void Error_inRequestBeforeGettingArguments(char endCharacter)
{
    if ('\0' != endCharacter)
    {
        fprintf(stderr, "Error_inRequestBeforeGettingArguments: request body overflow.\n");
        exit(1);
    }
}

void Error_inResponseWhileConstructingWithMaxLength(int maxLength)
{
    if (maxLength < 2)
    {
        fprintf(stderr, "Error_inResponseWhileConstructingWithMaxLength: maximum response length %d is too small.\n", maxLength);
        exit(1);
    }
}

void Error_inResponseBeforeLength(char endCharacter)
{
    if ('\0' != endCharacter)
    {
        fprintf(stderr, "Error_inResponseBeforeLength: resopnse body overflow.\n");
        exit(1);
    }
}

void Error_inResponseBeforeAddingNumber(char endCharacter)
{
    if ('\0' != endCharacter)
    {
        fprintf(stderr, "Error_inResponseBeforeAddingNumber: resopnse body overflow.\n");
        exit(1);
    }
}

void Error_inServerAfterForking(int processId)
{
    if (-1 == processId)
    {
        fprintf(stderr, "Error_inServerAfterForking.\n");
        exit(1);
    }
}
