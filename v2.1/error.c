#include "felys.h"


void
raise(ErrorType type, char const * msg)
{
    ElyError * const self = _error_init(type, msg);
    _push_error(__error__, self);
}


void 
_print_error_free_mem(errors *self)
{
    while (self->top > -1) {
        ElyError *err = _pop_error(self);
        printf("  "RED("%s")": %s\n", _get_error(err->type), err->msg);
        FREE(err);
    }
}


static char const *
_get_error(ErrorType type)
{
    switch (type) {
        case SysError: return "SysError";
        case ObjError: return "ObjError";
        case CvtError: return "CvtError";
        case DelError: return "DelError";
        case CalError: return "CalError";
        default: return "UnknownError";
    }
}


static ElyError *
_error_init(ErrorType type, char const *msg)
{
    ElyError *err = CALLOC(1, ElyError);
    if (err == NULL) {
        printf(RED("CRITICAL: FAILED TO ALLOCATE EMEORY FOR ERRORS"));
        exit(1);
    }
    err->type = type;
    err->msg = msg;
    return err;
}


static void
_push_error(errors *self, ElyError * const err)
{
    if (self->top < SIZE-1) {
        self->data[++self->top] = err;
    } else {
        printf(RED("CRITICAL: ERROR STACK OVERFLOW"));
        exit(1);
    }
}


static ElyError *
_pop_error(errors *self)
{
    if (self->top > -1) {
        return self->data[self->top--];
    } else {
        printf(RED("CRITICAL: ERROR STACK INVALID INDEX"));
        exit(1);
    }
}