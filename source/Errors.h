#ifndef ERRORS_H
#define ERRORS_H

#include "CountError.h"
#include "DirectionError.h"
#include "Error.h"
#include "GapError.h"
#include "LinkError.h"
#include "NodeError.h"

struct Errors;

struct Errors * Errors_construct(struct Error * error);

void Errors_destruct(struct Errors * this);

struct CountError * Errors_makeCountError(struct Errors * this);

struct DirectionError * Errors_makeDirectionError(struct Errors * this);

struct GapError * Errors_makeGapError(struct Errors * this);

struct LinkError * Errors_makeLinkError(struct Errors * this);

struct NodeError * Errors_makeNodeError(struct Errors * this);

#endif

