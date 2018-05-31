#ifndef ERRORS_H
#define ERRORS_H

#include "CountError.h"
#include "DirectionError.h"
#include "Error.h"
#include "LinkError.h"
#include "NetError.h"
#include "NodeError.h"
#include "StarError.h"

struct Errors;

struct Errors * Errors_construct(struct Error * error);

void Errors_destruct(struct Errors * this);

struct CountError * Errors_makeCountError(struct Errors * this);

struct DirectionError * Errors_makeDirectionError(struct Errors * this);

struct LinkError * Errors_makeLinkError(struct Errors * this);

struct NetError * Errors_makeNetError(struct Errors * this);

struct NodeError * Errors_makeNodeError(struct Errors * this);

struct StarError * Errors_makeStarError(struct Errors * this);

#endif

