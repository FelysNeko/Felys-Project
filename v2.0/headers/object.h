#ifndef __OBJECT_H__
#define __OBJECT_H__
#include "typedef.h"


ElyObject *new(ElyType, size_t *);
bool assign(ElyObject *, char *, size_t);
bool refer(ElyObject *, ElyObject **, size_t, size_t *);
void delete(ElyObject *, size_t *);
static void empty(ElyObject *, size_t *);


#endif