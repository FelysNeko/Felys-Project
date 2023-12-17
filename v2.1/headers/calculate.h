#ifndef __CALCULATE_H__
#define __CALCULATE_H__


ElyObject * _object_addition(ElyObject *, ElyObject *);
static char *_expand_string_from_head(char *, long, long);
static long _object_abs_larger(ElyObject *, ElyObject *);
static char *_tens_complement(char *, long, long, long, long);
static long _locate_decimal_point(char *, long);
static char *_aligned_number_add(char *, char *, long *);
static char * _tens_format(char *data, long, long, long, long);


typedef struct __calc__ {
    ElyObject *(*add)(ElyObject *, ElyObject *);
} __calc__;

extern __calc__ calc;


#endif