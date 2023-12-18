#include "felys.h"


int main(void)
{
    ElyObject *x, *y, *me, *array, *result, *all;
    EXEC(x = obj.init(NUMBER));
    EXEC(y = obj.init(NUMBER));
    EXEC(me = obj.init(STRING));
    EXEC(array = obj.init(ITERABLE));
    EXEC(all = obj.init(ITERABLE));

    EXEC(obj.assign(x, "-0.0", 4));
    EXEC(obj.assign(y, "+0.0", 4));
    EXEC(result = calc.add(x, y));

    ElyObject *sub[3] = {x, y, result};
    ElyObject *temp[2] = {array, me};

    EXEC(obj.assign(me, "felys", 5));
    EXEC(obj.store(array, sub, 3));
    EXEC(obj.store(all, temp, 2));

    obj.print(all, '\n');
    EXEC(obj.del(all));

end:
    summarize(__count__, __error__);
    return 0;
}