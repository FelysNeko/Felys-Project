#include "felys.h"


size_t _counter = 0;
size_t * const __count__ = &_counter;


ErrorStack _errorstack = {
    .data = {NULL},
    .top = -1
};
ErrorStack * const __error__ = &_errorstack;


ElyStack _callstack = {
    .data = {NULL},
    .top = -1
};
ElyStack * const __callstk__ =  &_callstack;


ElyStack _varstack = {
    .data = {NULL},
    .top = -1
};
ElyStack * const __varstk__ =  &_varstack;


__object__ obj = {
    .init = _object_init,
    .assign = _object_assign,
    .store = _object_store,
    .del = _object_delete,
    .print = _object_print
};


__calculate__ calc = {
    .add = _object_addition,
    .sub = _object_subtraction,
    .mul = _object_multiplcation,
    .lgr = _object_larger,
    .smr = _object_smaller,
    .eql = _object_equal,
};


__stack__ stk = {
    .pop = _pop_stack,
    .push = _push_stack,
};