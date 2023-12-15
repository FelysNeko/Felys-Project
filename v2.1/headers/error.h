#ifndef __ERROR_H__
#define __ERROR_H__
#include "core.h"
#include "define.h"


typedef struct error {
    ElyError *data[SIZE];
    int top;
} error;


void raise(ErrorType, char const *);
void _print_error_free_mem(error *);
static char const *_get_error(ErrorType);
static ElyError *_error_init(ErrorType, char const *);
static void _push_error(error *, ElyError *);
static ElyError *_pop_error(error *);


extern error _error_stack;
extern error * const __error__;

#endif
