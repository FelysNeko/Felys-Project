#ifndef __CALLSTACK_H__
#define __CALLSTACK_H__
#include "define.h"
#include "core.h"


typedef struct ElyStack {
    ElyObject *data[SIZE];
    int top;
} ElyStack;


bool _push_stack(ElyStack *, ElyObject *);
ElyObject *_pop_stack(ElyStack *);


extern ElyStack _callstack;
extern ElyStack _varstack;
extern ElyStack * const __callstk___;
extern ElyStack * const __varstk__;


typedef struct __stack__ {
    bool (*push)(ElyStack *, ElyObject *);
    ElyObject *(*pop)(ElyStack *);
} __stack__;

extern __stack__ stk;


#endif