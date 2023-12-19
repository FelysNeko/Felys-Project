#ifndef __CALCULATE_H__
#define __CALCULATE_H__


ElyObject * _object_addition(ElyObject *, ElyObject *);
ElyObject *_object_subtraction(ElyObject *, ElyObject *);
static char *_strnum_align(char *, size_t, size_t, size_t, size_t);
static char *_strnum_add_fi(char *, char *, size_t *);
static char *_strnum_sub_fi(char *, char *, size_t *, bool *);
static size_t _locate_deci_point(char *, size_t);
static char *_strnum_insert_head_fi(char *, size_t *, char);
static char *_strnum_complement_fi(char *, size_t);

typedef struct __calc__ {
    ElyObject *(*add)(ElyObject *, ElyObject *);
    ElyObject *(*sub)(ElyObject *, ElyObject *);
} __calc__;

extern __calc__ calc;


#endif