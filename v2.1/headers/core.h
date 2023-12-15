#ifndef __CORE_H__
#define __CORE_H__


typedef enum ElyType {
    NONE,
    NUMBER,
    STRING,
    ITERABLE,
} ElyType;


typedef struct ElyObject {
    ElyType type;
    size_t size;
    char *data;
    struct ElyObject **iter;
} ElyObject;


typedef struct ElyError {
    char const *msg;
} ElyError;


#endif