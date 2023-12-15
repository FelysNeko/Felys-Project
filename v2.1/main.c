#include "felys.h"


int main(void)
{
    ElyObject *x = obj.init(NUMBER);
    obj.assign(x, "+1.3", 4);
    obj.assign(x, "+1.0", 4);

    ElyObject *y = obj.init(NUMBER);
    obj.assign(y, "-3.1", 4);

    ElyObject *z = obj.init(STRING);
    obj.assign(z, "felys", 5);

    ElyObject *temp[3] = {x, y, z};

    ElyObject *arr = obj.init(ITERABLE);
    obj.store(arr, temp, 3);

    obj.print(arr, '\n');

    obj.del(arr);

end:
    summarize(__count__, __error__);
    return 0;
}