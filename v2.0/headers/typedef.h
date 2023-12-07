#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include "define.h"


typedef enum FeType {
    NONE,
    INTEGER,
    DECIMAL,
    RATIONAL,
    STRING,
    ITERABLE,
} FeType;


typedef struct FeObject {
    FeType type;
    char raw[MAX];
    struct FeObject *extend;
} FeObject;


#endif