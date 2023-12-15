#ifndef __ERROR_H__
#define __ERROR_H__
#include "core.h"
#include "define.h"


typedef struct errors {
    ElyError *data[SIZE];
    int top;
} errors;


void raise(ErrorType, char const *);
void _print_error_free_mem(errors *);
static char const *_get_error(ErrorType);
static ElyError *_error_init(ErrorType, char const *);
static void _push_error(errors *, ElyError *);
static ElyError *_pop_error(errors *);


extern errors _error_stack;
extern errors * const __error__;

#endif
