#include "define.h"

#ifndef __TYPEDEF_H
#define __TYPEDEF_H

typedef char container[MAX][LEN];

typedef struct{
    char name[LEN];
    double value;
}var;

typedef struct Layer{
    struct Layer *next;
    int scope;
    var body[MAX];
}lyr;

typedef struct Command{
    struct Command *next;
    struct Command *jump;
    char *expr;
    char *type;
    int index;
    int scope;
}cmd;

typedef struct{
    double body[MAX];
    int top;
}stack;


#endif