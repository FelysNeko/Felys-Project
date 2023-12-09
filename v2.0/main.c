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

    ElyObject *array = new(ITERABLE, cp);
    refer(array, temp, 2, cp);

    printf("%p\n", array);
    printf("%s\n", array->data);
    printf("%s\n", array->iter[0]->data);
    printf("%s\n", array->iter[1]->data);
    printf("%lu\n", array->size);

    delete(array, cp);
    printf("%lu\n", counter);

    return 0;
}