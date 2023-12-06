#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include "define.h"


typedef enum type {
    NONE,
    INTEGER,
    DECIMAL,
    RATIONAL,
    STRING,
    POINTER,
} type;


typedef enum bool {
    FALSE,
    TRUE,
} bool;


typedef struct object {
    type datatype;
    bool iterable;
    char content[MAX];
} object;


#endif