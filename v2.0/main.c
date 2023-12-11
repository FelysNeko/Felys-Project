#include "felys.h"

size_t counter = 0;
size_t * const cp = &counter;


int main(void)
{
    ElyObject *o1 = obj_new(INTEGER, cp);
    obj_assign(o1, "123456789123456789123456789987654321987654321987654321", 54);

    ElyObject *o2 = obj_new(INTEGER, cp);
    obj_assign(o2, "987654321987654321987654321123456789123456789123456789", 54);

    ElyObject *s = obj_new(STRING, cp);
    obj_assign(s, "felys", 5);

    ElyObject *r = obj_add_obj(o1, o2, cp);

    ElyObject *temp[] = {o1, o2, r, s};

    ElyObject *array = obj_new(ITERABLE, cp);
    obj_refer(array, temp, 4, cp);

    obj_print(array, '\n');
    obj_delete(array, cp);

    printf("%lu pieces of memory unfreed\n", counter);
    return 0;
}