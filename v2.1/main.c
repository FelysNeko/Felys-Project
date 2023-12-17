#include "felys.h"


int main(void)
{
    ElyObject *x, *y, *me, *array, *result, *all;

    EXEC(x = obj.init(NUMBER));
    EXEC(y = obj.init(NUMBER));
    EXEC(me = obj.init(STRING));
    EXEC(array = obj.init(ITERABLE));
    EXEC(all = obj.init(ITERABLE));


    EXEC(obj.assign(x, "+464243676710.2342424554525356", 30));
    EXEC(obj.assign(y, "-20245555454672452.42345264256", 30));
    EXEC(result = calc.add(y, x));
    EXEC(obj.assign(me, "felys", 5));

    ElyObject *sub[3] = {x, y, result};
    ElyObject *temp[2] = {array, me};
    EXEC(obj.store(array, sub, 3));
    EXEC(obj.store(all, temp, 2));

    obj.print(all, '\n');
    obj.del(all);

end:
    summarize(__count__, __error__);
    return 0;
}