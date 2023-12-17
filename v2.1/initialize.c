#include "felys.h"


long _counter = 0;
long * const __count__ = &_counter;


errors _error_stack = {
    .data = {NULL},
    .top = -1
};
errors * const __error__ = &_error_stack;


__object__ obj = {
    .init = _object_init,
    .assign = _object_assign,
    .store = _object_store,
    .del = _object_delete,
    .print = _object_print
};


__calc__ calc = {
    .add = _object_addition,
};