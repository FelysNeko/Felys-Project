#include "felys.h"


ElyObject *
obj_add_obj(ElyObject *lhs, ElyObject *rhs, size_t *cp)
{
    if (lhs->type==INTEGER && rhs->type==INTEGER) {
        return int_add_int(lhs, rhs, cp);
    } else {
        goto error;
    }

error:
    raise("operation not supported");
    return NULL;
}


static ElyObject *
int_add_int(ElyObject *lhs, ElyObject *rhs, size_t *cp)
{
    if (lhs->size > rhs->size) {
        ElyObject *temp = rhs;
        rhs = lhs;
        lhs = temp;
    }

    char * const result = (char *)calloc(rhs->size+1, sizeof(char));
    if (result == NULL) {
        goto error;
    }

    size_t diff = rhs->size - lhs->size;
    bool carry = false;
    
    for (int i=lhs->size-1; i>=0; --i) {
        int temp = char_to_int(lhs->data[i]) + char_to_int(rhs->data[diff+i]) + carry;
        if ((carry = (temp >= 10))) {
            temp %= 10;
        }
        result[diff+i+1] = int_to_char(temp);
    }

    for (int i=diff-1; i>=0; --i) {
        int temp = char_to_int(rhs->data[i]) + carry;
        if ((carry = (temp >= 10))) {
            temp %= 10;
        }
        result[i+1] = int_to_char(temp);
    }

    if (carry) {
        result[0] = '1';
    }

    ElyObject *ans = obj_new(INTEGER, cp);
    obj_assign(ans, (carry?result:result+1), rhs->size+carry);
    free(result);
    return ans;

error:
    raise("failed to add two objects");
    return NULL;
}
