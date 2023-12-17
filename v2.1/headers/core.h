#ifndef __CORE_H__
#define __CORE_H__


typedef enum ErrorType {
    SystemError,
    ObjectError,
    ConvertError,
    DeleteError,
} ErrorType;


typedef enum ElyType {
    NUMBER,
    STRING,
    ITERABLE,
} ElyType;


typedef struct ElyObject {
    ElyType type;
    long size;
    char *data;
    struct ElyObject **iter;
} ElyObject;


typedef struct ElyError {
    ErrorType type;
    char const *msg;
} ElyError;


#endif