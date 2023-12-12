#ifndef __OBJECT_H__
#define __OBJECT_H__
#include "typedef.h"


ElyObject *obj_new(ElyType);
void obj_assign(ElyObject *, char *, size_t);
void obj_refer(ElyObject *, ElyObject **, size_t);
void obj_delete(ElyObject *);
static void _obj_iter_delete(ElyObject *);
static void _obj_data_delete(ElyObject *);
void obj_print(ElyObject *, char);
static void _obj_data_print(ElyObject *);
static void _obj_iter_print(ElyObject *);


typedef struct __object__ {
    ElyObject *(*new)(ElyType);
    void (*assign)(ElyObject *, char *, size_t);
    void (*refer)(ElyObject *, ElyObject **, size_t);
    void (*del)(ElyObject *);
    void (*print)(ElyObject *, char);
} __object__;

extern __object__ obj;


#endif