#ifndef __ARITHMETIC_H__
#define __ARITHMETIC_H__
#include "typedef.h"


ElyObject *obj_add_obj(ElyObject *, ElyObject *, size_t *);
static ElyObject *int_add_int(ElyObject *, ElyObject *, size_t *);


#endif