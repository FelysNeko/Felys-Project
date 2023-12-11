#include "felys.h"

size_t counter = 0;
size_t * const cp = &counter;


int main(void)
{
    ElyObject *o1 = obj_new(STRING, cp);
    obj_assign(o1, "Hello", 5);

    ElyObject *o2 = obj_new(NUMBER, cp);
    obj_assign(o2, "123", 3);

    ElyObject *temp[2] = {o1, o2};

    ElyObject *a1 = obj_new(ITERABLE, cp);
    obj_refer(a1, temp, 2, cp);

    ElyObject *a2 = obj_new(ITERABLE, cp);
    obj_refer(a2, &a1, 1, cp);
    
    obj_print(a2, '\n');
    obj_delete(a2, cp);

    printf("[%lu]\n", counter);
    return 0;
}