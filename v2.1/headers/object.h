#ifndef __OBJECT_H__
#define __OBJECT_H__
#include "core.h"


ElyObject *_object_init(ElyType);
bool _object_assign(ElyObject *, char *, size_t);
bool _object_store(ElyObject *, ElyObject **, size_t);
bool _object_delete(ElyObject *);
bool _object_print(ElyObject *, char);


typedef struct __object__ {
    ElyObject *(*init)(ElyType);
    bool (*assign)(ElyObject *, char *, size_t);
    bool (*store)(ElyObject *, ElyObject **, size_t);
    bool (*del)(ElyObject *);
    bool (*print)(ElyObject *, char);
} __object__;

extern __object__ obj;


#endif