#include "felys.h"


int main(void)
{
    ElyObject *a, *b, *r;
    EXEC(a = obj.init(NUMBER));
    EXEC(obj.assign(a, "+99.9", 5));
    EXEC(b = obj.init(NUMBER));
    EXEC(obj.assign(b, "-99.9", 5));

    EXEC(r = calc.sub(a, b));
    obj.print(r, '\n');

    EXEC(obj.del(a));
    EXEC(obj.del(b));
    EXEC(obj.del(r));


end:
    summarize(__count__, __error__);
    return 0;
}