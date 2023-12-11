#ifndef __OBJECT_H__
#define __OBJECT_H__
#include "typedef.h"


ElyObject *obj_new(ElyType, size_t *);
void obj_assign(ElyObject *, char *, size_t);
void obj_refer(ElyObject *, ElyObject **, size_t, size_t *);
void obj_delete(ElyObject *, size_t *);
static void obj_iter_delete(ElyObject *, size_t *);
static void obj_data_delete(ElyObject *);
void obj_print(ElyObject *, char);
static void obj_data_print(ElyObject *);
static void obj_iter_print(ElyObject *);


#endif