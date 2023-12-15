#ifndef __OBJECT_H__
#define __OBJECT_H__
#include "core.h"


ElyObject *_object_init(ElyType);
bool _object_assign(ElyObject *, char *, size_t);
bool _object_store(ElyObject *, ElyObject **, size_t);
bool _object_delete(ElyObject *);
bool _object_print(ElyObject *, char);
static bool _delete_object_data(ElyObject *);
static bool _delete_object_iter(ElyObject *);
static bool _data_check(ElyObject *, char *, size_t);
static bool _number_check(char *, size_t);
static bool _string_check(char *, size_t);


typedef struct __object__ {
    ElyObject *(*init)(ElyType);
    bool (*assign)(ElyObject *, char *, size_t);
    bool (*store)(ElyObject *, ElyObject **, size_t);
    bool (*del)(ElyObject *);
    bool (*print)(ElyObject *, char);
} __object__;

extern __object__ obj;


#endif