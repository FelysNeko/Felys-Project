#ifndef __ERROR_H__
#define __ERROR_H__
#include "core.h"
#include "define.h"


typedef struct ElyErrorstack {
    ElyError *data[SIZE];
    int top;
} ElyErrorstack;


void raise(ErrorType, char const *);
void _print_error_free_mem(ElyErrorstack *);
static char const *_get_error(ErrorType);
static ElyError *_error_init(ErrorType, char const *);
static void _push_error(ElyErrorstack *, ElyError *);
static ElyError *_pop_error(ElyErrorstack *);


extern ElyErrorstack _errorstack;
extern ElyErrorstack * const __error__;

#endif
