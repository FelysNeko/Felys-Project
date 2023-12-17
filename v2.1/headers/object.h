#ifndef __OBJECT_H__
#define __OBJECT_H__
#include "core.h"


ElyObject *_object_init(ElyType);
bool _object_assign(ElyObject *, char *, long);
bool _object_store(ElyObject *, ElyObject **, long);
bool _object_delete(ElyObject *);
void _object_print(ElyObject *, char);
static bool _delete_object_data(ElyObject *);
static bool _delete_object_iter(ElyObject *);
static bool _data_check(ElyObject *, char *, long);
static bool _number_check(char *, long);
static bool _string_check(char *, long);
static bool _iter_check(ElyObject *, long);
static void _print_data(ElyObject *);
static void _print_iter(ElyObject *);


typedef struct __object__ {
    ElyObject *(*init)(ElyType);
    bool (*assign)(ElyObject *, char *, long);
    bool (*store)(ElyObject *, ElyObject **, long);
    bool (*del)(ElyObject *);
    void (*print)(ElyObject *, char);
} __object__;

extern __object__ obj;


#endif