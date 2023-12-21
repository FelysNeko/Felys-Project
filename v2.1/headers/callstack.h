#ifndef __CALLSTACK_H__
#define __CALLSTACK_H__
#include "core.h"


typedef struct ElyCallstack {
    ElyObject *data[SIZE];
    int top;
} ElyCallstack;


bool _push_callstack(ElyCallstack *, ElyObject *);
ElyObject *_pop_callstack(ElyCallstack *);


extern ElyCallstack _callstack;
extern ElyCallstack * const __stack___;


typedef struct __callstack__ {
    bool (*push)(ElyCallstack *, ElyObject *);
    ElyObject *(*pop)(ElyCallstack *);
} __callstack__;

extern __callstack__ stk;


#endif