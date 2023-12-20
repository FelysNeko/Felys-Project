#include "felys.h"


bool 
_push_callstack(ElyCallstack *cstk, ElyObject *data)
{
    if (cstk->top < SIZE-1) {
        cstk->data[++cstk->top] = data;
        return true;
    }

exception:
    raise(StkError, "<_push_callstack> callstack overflow");
    return false;
}


ElyObject * 
_pop_callstack(ElyCallstack *cstk)
{
    if (cstk->top > -1) {
        return cstk->data[cstk->top--];
    }

exception:
    raise(StkError, "<_pop_callstack> callstack is empty");
    return NULL;
}