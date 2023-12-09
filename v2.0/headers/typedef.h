#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__


typedef enum ElyType {
    NONE,
    NUMBER,
    STRING,
    RATIONAL,
    ITERABLE,
} ElyType;


typedef struct ElyObject {
    ElyType type;
    size_t size;
    char *data;
    struct ElyObject **iter;
} ElyObject;


#endif