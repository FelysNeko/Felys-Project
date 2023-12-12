#include "felys.h"

size_t counter = 0;

__object__ obj = {
    .new = obj_new,
    .del = obj_delete,
    .assign = obj_assign,
    .refer = obj_refer,
    .print = obj_print,
};