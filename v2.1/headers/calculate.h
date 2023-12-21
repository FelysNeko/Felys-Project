#ifndef __CALCULATE_H__
#define __CALCULATE_H__


ElyObject * _object_addition(ElyObject *, ElyObject *);
ElyObject *_object_subtraction(ElyObject *, ElyObject *);
ElyObject *_object_multiplcation(ElyObject *, ElyObject *);
ElyObject *_object_larger(ElyObject *, ElyObject *);
ElyObject *_object_smaller(ElyObject *, ElyObject *);
ElyObject *_object_equal(ElyObject *, ElyObject *);
static size_t _object_comapare(ElyObject *, ElyObject *);
static char *_strnum_align(char *, size_t, size_t, size_t, size_t);
static char *_strnum_add_fi(char *, char *, size_t *);
static char *_strnum_sub_fi(char *, char *, size_t *, bool *);
static size_t _locate_deci_point(char *, size_t);
static char *_strnum_insert_head_fi(char *, size_t *, char);
static char *_strnum_complement_fi(char *, size_t);
static char *_strnum_multi_bychar(char *, size_t *, char);
static char *_strnum_shift_right_fi(char *, size_t *, size_t);
static char *_strnum_shift_left_fi(char *, size_t *, size_t);


typedef struct __calculate__ {
    ElyObject *(*add)(ElyObject *, ElyObject *);
    ElyObject *(*sub)(ElyObject *, ElyObject *);
    ElyObject *(*mul)(ElyObject *, ElyObject *);
    ElyObject *(*lgr)(ElyObject *, ElyObject *);
    ElyObject *(*smr)(ElyObject *, ElyObject *);
    ElyObject *(*eql)(ElyObject *, ElyObject *);
} __calculate__;

extern __calculate__ calc;


#endif