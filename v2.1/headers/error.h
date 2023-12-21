#ifndef __ERROR_H__
#define __ERROR_H__
#include "core.h"
#include "define.h"


typedef struct ErrorStack {
    ElyError *data[SIZE];
    int top;
} ErrorStack;


void raise(ErrorType, char const *);
void _print_error_free_mem(ErrorStack *);
static char const *_get_error(ErrorType);
static ElyError *_error_init(ErrorType, char const *);
static void _push_error(ErrorStack *, ElyError *);
static ElyError *_pop_error(ErrorStack *);


extern ErrorStack _errorstack;
extern ErrorStack * const __error__;


#endif
