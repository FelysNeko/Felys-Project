#include "felys.h"


ElyObject *
_object_subtraction(ElyObject *lhs, ElyObject *rhs)
{
    rhs->data[0] = (rhs->data[0]=='+') ? '-' : '+';
    ElyObject * result = _object_addition(lhs, rhs);
    if (result == NULL) {
        goto exception;
    }
    rhs->data[0] = (rhs->data[0]=='+') ? '-' : '+';

    return result;

exception:
    raise(CalError, "<_object_addition> failed to minus two objects");
    return NULL;
}


ElyObject *
_object_addition(ElyObject *lhs, ElyObject *rhs)
{
    if (lhs->type!=NUMBER || rhs->type!=NUMBER) {
        raise(CalError, "<_object_addition> both objects' type should be number");
        goto exception;
    }

    size_t const ldp = _locate_deci_point(lhs->data+1, lhs->size-1);
    size_t const rdp = _locate_deci_point(rhs->data+1, rhs->size-1);
    if ((ldp==lhs->size-1) || (rdp==rhs->size-1)) {
        goto exception;
    }
    
    size_t const left = MAX(ldp, rdp);
    size_t const right = MAX(lhs->size-ldp-2, rhs->size-rdp-2);
    size_t size = left + right +1;

    char * const flhs = _strnum_align(lhs->data+1, lhs->size-1, ldp, left, right);
    char * const frhs = _strnum_align(rhs->data+1, rhs->size-1, rdp, left, right);
    if (flhs==NULL || frhs==NULL) {
        goto exception;
    }

    bool const lsgn = (lhs->data[0]=='+');
    bool const rsgn = (rhs->data[0]=='+');
    bool sign = true;

    char *temp = NULL;
    if (lsgn > rsgn) {
        temp = _strnum_sub_fi(flhs, frhs, &size, &sign);
    } else if (lsgn < rsgn) {
        temp = _strnum_sub_fi(frhs, flhs, &size, &sign);
    } else {
        temp = _strnum_add_fi(flhs, frhs, &size);
        sign = lsgn;
    }

    if (temp == NULL) {
        goto exception;
    }

    char * const data = (sign) ? 
    _strnum_insert_head_fi(temp, &size, '+') :
    _strnum_insert_head_fi(temp, &size, '-');
    if (data == NULL) {
        goto exception;
    }

    ElyObject * const result = _object_init(NUMBER);
    if (result == NULL) {
        goto exception;
    }

    if (_object_assign(result, data, size) == false) {
        goto exception;
    }

    FREE(data);
    return result;

exception:
    raise(CalError, "<_object_addition> failed to add two objects");
    return NULL;
}


static size_t
_locate_deci_point(char *data, size_t size)
{
    for (size_t i=0; i<size; ++i) {
        if (data[i] == '.') {
            return i;
        }
    }

exception:
    raise(CalError, "<_locate_deci_point> cannot locate decimal point");
    return size;
}


static char *
_strnum_align(char *data, size_t size, size_t point, size_t left, size_t right)
{
    char * const result = CALLOC(left+right+1, char);
    if (result == NULL) {
        raise(SysError, "<calloc> failed to allocate new memory");
        goto exception;
    }
    
    for (size_t index=0; index<left+right+1; ++index) {
        size_t temp = left-point;
        if ((index<temp) || (temp+size-1<index)) {
            result[index] = '0';
        } else {
            result[index] = data[index-temp];
        }
    }

    return result;

exception:
    raise(CalError, "<_strnum_align> cannot format the strnum");
    return NULL;
}


static char *
_strnum_add_fi(char *lhs, char *rhs, size_t *sp)
{
    size_t const size = *sp;
    char * const result = CALLOC(size, char);
    if (result == NULL) {
        raise(SysError, "<calloc> failed to allocate new memory");
        goto exception;
    }

    bool carry = false;
    for (size_t i=size-1; 0<=i && i<=size-1; --i) {
        size_t lval = _char_to_size_t(lhs[i]);
        size_t rval = _char_to_size_t(rhs[i]);
        if (lval==10 || rval==10) {
            goto exception;
        }

        if (lval=='.' && rval=='.') {
            result[i] = '.';
            continue;
        }

        int temp = lval + rval + carry;
        if ((carry = (temp>=10))) {
            temp %= 10;
        }
        result[i] = _size_t_to_char(temp);
    }

    FREE(lhs);
    FREE(rhs);

    if (carry) {
        char * const alter = _strnum_insert_head_fi(result, sp, '1');
        if (alter == NULL) {
            goto exception;
        }
        return alter;
    }

    return result;

exception:
    raise(CalError, "<_strnum_add_fi> failed to add two strnum");
    return NULL;
}


static char *
_strnum_insert_head_fi(char *data, size_t *sp, char c)
{
    size_t const size = *sp;
    char * const result = CALLOC(size+1, char);
    if (result == NULL) {
        raise(SysError, "<calloc> failed to allcoate new memory");
        goto exception;
    }

    result[0] = c;
    for (size_t i=0; i<size; ++i) {
        result[i+1] = data[i];
    }
    FREE(data);
    ++*sp;
    return result;

exception:
    raise(CalError, "<_strnum_insert_head_fi> failed to insert char to front");
    return NULL;
}


static char *
_strnum_sub_fi(char *pos, char *neg, size_t *sp, bool *sign)
{
    size_t const size = *sp;
    char * const result = CALLOC(size, char);
    if (result == NULL) {
        raise(SysError, "<calloc> failed to allocate new memory");
        goto exception;
    }

    bool carry = false;
    for (size_t i=size-1; 0<=i && i<=size-1; --i) {
        size_t pval = _char_to_size_t(pos[i]);
        size_t nval = _char_to_size_t(neg[i]);
        if (pval==10 || nval==10) {
            goto exception;
        }

        if (pval=='.' && nval=='.') {
            result[i] = '.';
            continue;
        }

        size_t temp = pval - nval - carry;
        if ((carry = (temp>pval))) {
            temp += 10;
        }
        result[i] = _size_t_to_char(temp);
    }

    FREE(pos);
    FREE(neg);

    if (carry) {
        char * const alter = _strnum_complement_fi(result, size);
        if (alter == NULL) {
            goto exception;
        }
        *sign = false;
        return alter;
    }

    return result;

exception:
    raise(CalError, "<_strnum_add_fi> failed to sub two strnum");
    return NULL;

}


static char *
_strnum_complement_fi(char *data, size_t size)
{
    char * const result = CALLOC(size, char);
    if (result == NULL) {
        raise(SysError, "<calloc> failed to allocate new memory");
        goto exception;
    }

    bool carry = true;
    for (size_t i=size-1; 0<=i && i<=size-1; --i) {
        size_t temp = _char_to_size_t(data[i]);
        if (temp == 10) {
            goto exception;
        }

        if (temp == '.') {
            result[i] = '.';
            continue;
        }

        temp = 9 - temp + carry;
        if ((carry = (temp>=10))) {
            temp %= 10;
        }
        result[i] = _size_t_to_char(temp);
    }

    FREE(data);
    return result;

exception:
    raise(CalError, "<_strnum_complement_fi> failed to perform complement operation");
    return NULL;
}


ElyObject *
_object_multiplcation(ElyObject *lhs, ElyObject *rhs)
{
    if (lhs->type!=NUMBER || rhs->type!=NUMBER) {
        raise(CalError, "<_object_multiplcation> both objects' type should be number");
        goto exception;
    }

    size_t const rdp = _locate_deci_point(rhs->data+1, rhs->size-1);
    if (rdp==rhs->size-1) {
        goto exception;
    }

    bool const sign = (lhs->data[0]==rhs->data[0]);
    ElyObject *result = _object_init(NUMBER);
    if (result == NULL) {
        goto exception;
    }

    if (_object_assign(result, "+0.0", 4) == false) {
        goto exception;
    }

    char * const rd = rhs->data+1;
    char * const ld = lhs->data+1;
    size_t const rs = rhs->size-1;
    size_t const ls = lhs->size-1;

    for (size_t i=0, ts=ls; i<rs; ++i, ts=ls) {
        if (rd[i] == '.') {
            continue;
        }

        char * const temp = _strnum_multi_bychar(ld, &ts, rd[i]);
        if (temp == NULL) {
            goto exception;
        }

        char * const shifted = (i<rdp) ?
        _strnum_shift_right_fi(temp, &ts, rdp-i-1) :
        _strnum_shift_left_fi(temp, &ts, i-rdp);
        if (shifted == NULL) {
            goto exception;
        }
        
        char * const data = _strnum_insert_head_fi(shifted, &ts, '+');
        if (data == NULL) {
            goto exception;
        }

        ElyObject * const each = _object_init(NUMBER);
        if (each == NULL) {
            goto exception;
        }

        if (_object_assign(each, data, ts) == false) {
            goto exception;
        }
        FREE(data);

        ElyObject *prev = result;
        result = _object_addition(result, each);
        
        if (_object_delete(each)==false || _object_delete(prev)==false) {
            goto exception;
        }
    }

    return result;

exception:
    raise(CalError, "<_object_multiplcation> failed to multiply two objects");
    return NULL;
}


static char *
_strnum_multi_bychar(char *data, size_t *sp, char c)
{
    size_t const size = *sp;
    char * const result = CALLOC(size, char);
    if (result == NULL) {
        raise(SysError, "<calloc> failed to allocate new memory");
        goto exception;
    }

    size_t carry = 0;
    for (size_t i=size-1; 0<=i && i<=size-1; --i) {
        size_t temp = _char_to_size_t(data[i]);
        size_t mult = _char_to_size_t(c);
        if (temp==10 || mult==10) {
            goto exception;
        }

        if (temp == '.') {
            result[i] = '.';
            continue;
        }

        temp = temp * mult + carry;
        if (temp > 9) {
            carry = temp/10;
            temp %= 10;
        } else {
            carry = 0;
        }
        result[i] = _size_t_to_char(temp);
    }

    if (carry) {
        char * const alter = _strnum_insert_head_fi(result, sp, _size_t_to_char(carry));
        if (alter == NULL) {
            goto exception;
        }
        return alter;
    }

    return result;

exception:
    raise(CalError, "<_strnum_multi_bychar> failed to multiply strnum by single char");
    return NULL;
}


static char *
_strnum_shift_right_fi(char *data, size_t *sp, size_t times)
{
    size_t size = *sp;
    char *result = CALLOC(size, char);
    if (result == NULL) {
        goto exception;
    }

    for (size_t i=0; i<size; ++i) {
        result[i] = data[i];
    }

    FREE(data);

    for (size_t c=0, ts=*sp; c<times; ++c, ts=*sp) {
        if (result[ts-2] == '.') {
            result = realloc(result, ts+1);
            if (result == NULL) {
                raise(SysError, "<realloc> failed to allocate new memory");
                goto exception;
            }
            SWAP(result[ts-1], result[ts-2], char);
            result[ts] = '0';
            ++(*sp);
        } else {
            for (size_t i=0; i<*sp; ++i) {
                if (result[i] == '.') {
                    SWAP(result[i], result[i+1], char);
                    break;
                }
            }
        }
    }

    return result;

exception:
    raise(CalError, "<_strnum_shift_right> failed to shift strnum");
    return NULL;
}


static char *
_strnum_shift_left_fi(char *data, size_t *sp, size_t times)
{
    size_t size = *sp;
    char *result = CALLOC(size, char);
    if (result == NULL) {
        goto exception;
    }

    for (size_t i=0; i<size; ++i) {
        result[i] = data[i];
    }

    FREE(data);

    for (size_t c=0, ts=*sp; c<times; ++c, ts=*sp) {
        if (result[1] == '.') {
            result = _strnum_insert_head_fi(result, sp, '0');
            if (result == NULL) {
                goto exception;
            }
            SWAP(result[1], result[2], char);
        } else {
            for (size_t i=0; i<*sp; ++i) {
                if (result[i] == '.') {
                    SWAP(result[i], result[i-1], char);
                    break;
                }
            }
        }
    }

    return result;

exception:
    raise(CalError, "<_strnum_shift_left> failed to shift strnum");
    return NULL;
}