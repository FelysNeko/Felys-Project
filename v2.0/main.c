#include "felys.h"

size_t counter = 0;
size_t * const cp = &counter;


int main(void)
{
    ElyObject *o1 = new(STRING, cp);
    assign(o1, "Hello", 6);

    ElyObject *o2 = new(NUMBER, cp);
    assign(o2, "123", 4);

    ElyObject *temp[2] = {o1, o2};

    ElyObject *a1 = new(ITERABLE, cp);
    refer(a1, temp, 2, cp);

    ElyObject *a2 = new(ITERABLE, cp);
    refer(a2, &a1, 1, cp);
    
    delete(a2, cp);
    printf("[%lu]\n", counter);

    return 0;
}