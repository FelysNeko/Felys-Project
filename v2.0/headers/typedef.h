#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__


typedef enum ElyType {
    NONE,
    INTEGER,
    DECIMAL,
    STRING,
    ITERABLE,
} ElyType;


typedef struct ElyObject {
    ElyType type;
    size_t size;
    char *data;
    struct ElyObject **iter;
} ElyObject;


#endif