#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include "define.h"


typedef enum ElyType {
    NONE,
    INTEGER,
    DECIMAL,
    RATIONAL,
    STRING,
    ITERABLE,
} ElyType;


typedef struct ElyObject {
    ElyType type;
    char raw[MAX];
    struct ElyObject *extend;
} ElyObject;


#endif