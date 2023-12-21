#include "felys.h"


size_t _counter = 0;
size_t * const __count__ = &_counter;


ElyErrorstack _errorstack = {
    .data = {NULL},
    .top = -1
};
ElyErrorstack * const __error__ = &_errorstack;


ElyCallstack _callstack = {
    .data = {NULL},
    .top = -1
};
ElyCallstack * const __stack__ =  &_callstack;


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
};


__callstack__ stk = {
    .pop = _pop_callstack,
    .push = _push_callstack,
};