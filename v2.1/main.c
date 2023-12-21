#include "felys.h"


int main(void)
{
    ElyObject *a, *b, *r;
    EXEC(a = obj.init(NUMBER));
    EXEC(obj.assign(a, "-12.54", 6));
    EXEC(b = obj.init(NUMBER));
    EXEC(obj.assign(b, "+112.32", 7));

    EXEC(r = calc.mul(a, b));
    obj.print(r, '\n');

    EXEC(obj.del(a));
    EXEC(obj.del(b));
    EXEC(obj.del(r));


end:
    summarize(__count__, __error__);
    return 0;
}