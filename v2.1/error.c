#include "felys.h"


void
raise(char const * msg)
{
    ElyError * const self = _error_init(msg);
    _push_error(__error__, self);
}


void 
_print_error_free_mem(error *self)
{
    while (self->top > -1) {
        ElyError *err = _pop_error(self);
        printf(RED("%s"), err->msg);
        FREE(err);
    }
}


static ElyError *
_error_init(char const *msg)
{
    ElyError *err = CALLOC(1, ElyError);
    if (err == NULL) {
        printf(RED("CRITICAL: cannot allocate memory for errors"));
        exit(1);
    }
    err->msg = msg;
    return err;
}


static void
_push_error(error *self, ElyError * const err)
{
    if (self->top < SIZE-1) {
        self->data[++self->top] = err;
    } else {
        printf(RED("CRITICAL: error stack overflow"));
        exit(1);
    }
}


static ElyError *
_pop_error(error *self)
{
    if (self->top > -1) {
        return self->data[self->top--];
    } else {
        printf(RED("CRITICAL: error stack invalid index"));
        exit(1);
    }
}