#ifndef OBJECT_H
#define OBJECT_H

#include "base.h"

// Copies an object.
typedef void* (*CopyFun)(void* object);

// Frees an object.
typedef void (*FreeFun)(void* object);

// Checks if two objects are equal.
typedef bool (*EqualFun)(void* object1, void* object2);

// Returns a dynamically allocated string representation of the object, 
// which the caller has to release.
typedef String (*ToStringFun)(void* object);

// Represents the class of an object. For each type 
// of object there is a single class instance.
typedef struct Class {
    CopyFun copy;
    FreeFun free;
    EqualFun equal;
    ToStringFun to_string;
} Class;

typedef struct Object {
    Class* class;
} Object;

#endif
