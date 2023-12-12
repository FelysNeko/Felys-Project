#include "felys.h"


int main(void)
{
    ElyObject *a = obj.new(INTEGER);
    obj.assign(a, "123", 3);

    ElyObject *b = obj.new(INTEGER);
    obj.assign(b, "321", 3);

    ElyObject *c = obj.new(STRING);
    obj.assign(c, "felys miao", 10);

    ElyObject *temp1[2] = {a, b};

    ElyObject *arr = obj.new(ITERABLE);
    obj.refer(arr, temp1, 2);

    ElyObject *temp2[2] = {arr, c};

    ElyObject *r = obj.new(ITERABLE);
    obj.refer(r, temp2, 2);

    obj.print(r, '\n');
    obj.del(r);

    summarize(counter);
    return 0;
}