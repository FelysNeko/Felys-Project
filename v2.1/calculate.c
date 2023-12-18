#include "felys.h"


ElyObject *
_object_addition(ElyObject *lhs, ElyObject *rhs)
{
    long lp = _locate_decimal_point(lhs->data, lhs->size) - 1;
    long rp = _locate_decimal_point(rhs->data, rhs->size) - 1;
    if (lp==lhs->size+1 || rp==rhs->size+1) {
        goto exception;
    }

    long left = MAX(lp, rp);
    long right = MAX(lhs->size-lp, rhs->size-rp)-2;
    long size = left + right + 1;

    char *lval = NULL;
    char *rval = NULL;
    if (lhs->data[0]=='+' && rhs->data[0]=='-') {
        lval = _tens_format(lhs->data+1, lhs->size-1, lp, left, right);
        rval = _tens_complement(rhs->data+1, rhs->size-1, rp, left, right);
    } else if (lhs->data[0]=='-' && rhs->data[0]=='+') {
        lval = _tens_complement(lhs->data+1, lhs->size-1, lp, left, right);
        rval = _tens_format(rhs->data+1, rhs->size-1, rp, left, right);
    } else {
        lval = _tens_format(lhs->data+1, lhs->size-1, lp, left, right);
        rval = _tens_format(rhs->data+1, rhs->size-1, rp, left, right);
    }
    if (lval==NULL || rval==NULL) {
        goto exception;
    }

    char *result = _aligned_number_add(lval, rval, &size);
    if (result == NULL) {
        goto exception;
    }

    FREE(lval);
    FREE(rval);

    long larger = _object_abs_larger(lhs, rhs);
    if (larger == -1) {
        goto exception;
    }

    bool sign = !((lhs->data[0]=='-' && rhs->data[0]=='-') || 
                (lhs->data[0]=='+' && rhs->data[0]=='-' && larger==0) ||
                (lhs->data[0]=='-' && rhs->data[0]=='+' && larger==1) ||
                (larger == 2));

    if (lhs->data[0]+rhs->data[0]=='+'+'-' && sign) {
        result[0] = '+';
    } else if (lhs->data[0]+rhs->data[0]=='+'+'-' && !sign) {
        char * const reversed = _tens_complement(result, size, left, left, right);
        if (reversed == NULL) {
            goto exception;
        }
        FREE(result);

        char * const temp = _expand_string_from_head(reversed, size, 1);
        if (temp == NULL) {
            goto exception;
        }
        FREE(reversed);

        temp[0] = '-';
        ++size;
        result = temp;
    } else {
        char * const temp = _expand_string_from_head(result, size, 1);
        if (temp == NULL) {
            goto exception;
        }
        FREE(result);

        ++size;
        temp[0] = sign? '+' : '-';
        result = temp;
    }


    ElyObject *object = _object_init(NUMBER);
    if (_object_assign(object, result, size) == false) {
        goto exception;
    }

    FREE(result);
    return object;

exception:
    raise(CalError, "<_object_addition> failed to add two objects");
    return NULL;
}


static char *
_expand_string_from_head(char *data, long size, long longer)
{
    char * const result = CALLOC(size+longer, char);
    if (result == NULL) {
        raise(SysError, "<calloc> failed to allocate new memory");
        goto exception;
    }

    for (long i=0; i<size; ++i) {
        result[i+longer] = data[i];
    }
    return result;

exception:
    raise(CalError, "<_expand_string_from_head> failed to expand string");
    return NULL;
}


static long
_object_abs_larger(ElyObject *lhs, ElyObject *rhs)
{
    long lp = _locate_decimal_point(lhs->data, lhs->size) - 1;
    long rp = _locate_decimal_point(rhs->data, rhs->size) - 1;
    if (lp==lhs->size+1 || rp==rhs->size+1) {
        goto exception;
    }

    long left = MAX(lp, rp);
    long right = MAX(lhs->size-lp, rhs->size-rp)-2;
    long size = left + right + 1;

    char * const lval = _tens_format(lhs->data+1, lhs->size-1, lp, left, right);
    char * const rval = _tens_format(rhs->data+1, rhs->size-1, rp, left, right);
    if (lval==NULL || rval==NULL) {
        goto exception;
    }

    long result = 2;
    for (long i=0; i<size; ++i) {
        if (lval[i] > rval[i]) {
            result = 1;
            break;
        } else if (lval[i] < rval[i]) {
            result = 0;
            break;
        }
    }

    FREE(lval);
    FREE(rval);
    return result;

exception:
    raise(CalError, "<_object_abs_larger> failed compare two objects' abslute vale");
    return -1;
}


static char *
_aligned_number_add(char *lhs, char *rhs, long *size)
{
    char * const result = CALLOC(*size, char);
    if (result == NULL) {
        raise(SysError, "<calloc> failed to allocate new memory");
        goto exception;
    }

    bool carry = false;
    for (long i=(*size)-1, lval, rval, temp; i>=0; --i) {
        lval = _char_to_int(lhs[i]);
        rval = _char_to_int(rhs[i]);
        if (lval == 10 || rval == 10) {
            goto exception;
        } else if ((lval=='.' && rval!='.') || (lval!='.' && rval=='.')) {
            goto exception;
        }

        if (lval == '.') {
            result[i] = '.';
        } else {
            temp = lval + rval + carry;
            if ((carry = (temp>9))) {
                temp %= 10;
            }
            result[i] = _int_to_char(temp);
        }
    }

    if (carry) {
        char * const temp = _expand_string_from_head(result, *size, 1);
        if (temp == NULL) {
            goto exception;
        }
        temp[0] = '1';
        
        ++(*size);
        FREE(result);
        return temp;
    }

    return result;

exception:
    raise(CalError, "<_aligned_number_add> failed to perform addition");
    return NULL;
}


static char *
_tens_format(char *data, long size, long point, long left, long right)
{
    char * const result = CALLOC(left+right+1, char);
    if (result == NULL) {
        raise(SysError, "<calloc> failed to allocate new memory");
        goto exception;
    }

    bool carry = true;
    long index = left + right;

    for (; left+(size-point)<=index; --index) {
        result[index] = '0';
    }

    for (long i=size-1, temp; 0<=i; --index, --i) {
        if ((temp = _char_to_int(data[i])) == 10) {
            goto exception;
        }
        result[index] = data[i];
    }

    for (; 0<=index; --index) {
        result[index] = '0';
    }

    return result;

exception:
    raise(CvtError, "<_tens_format> failed to perform tens format");
    return NULL;
}


static char *
_tens_complement(char *data, long size, long point, long left, long right)
{
    char * const result = CALLOC(left+right+1, char);
    if (result == NULL) {
        raise(SysError, "<calloc> failed to allocate new memory");
        goto exception;
    }

    bool carry = true;
    long index = left + right;

    for (; left+(size-point)<=index; --index) {
        result[index] = '0';
    }

    for (long i=size-1, temp; 0<=i; --index, --i) {
        if ((temp = _char_to_int(data[i])) == 10) {
            goto exception;
        }

        if (temp == '.') {
            result[index] = '.';
        } else {
            temp = 9 - temp + carry;
            if ((carry = (temp>9))) {
                temp %= 10;
            }
            result[index] = _int_to_char(temp);
        }
    }

    for (int temp; 0<=index; --index) {
        temp = 9 + carry;
        if ((carry = (temp>9))) {
            temp %= 10;
        }
        result[index] = _int_to_char(temp);
    }

    return result;

exception:
    raise(CalError, "<_tens_complement> failed to perform tens complement convertion");
    return NULL;
}


static long 
_locate_decimal_point(char *data, long size)
{
    for (long i=0; i<size; ++i) {
        if (data[i] == '.') {
            return i;
        }
    }

exception:
    raise(CalError, "<_locate_decimal_point> failed to find decimal point");
    return size;
}