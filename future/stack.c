#include "felys.h"


bool 
_push_stack(ElyStack *cstk, ElyObject *data)
{
    if (cstk->top < SIZE-1) {
        cstk->data[++cstk->top] = data;
        return true;
    }

exception:
    raise(StkError, "<_push_stack> callstack overflow");
    return false;
}


ElyObject * 
_pop_stack(ElyStack *cstk)
{
    if (cstk->top > -1) {
        return cstk->data[cstk->top--];
    }

exception:
    raise(StkError, "<_pop_stack> callstack is empty");
    return NULL;
}