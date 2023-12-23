#include "felys.h"


int main(void)
{
    ElyObject *a, *b, *r;
    EXEC(a = obj.init(NUMBER));
    EXEC(obj.assign(a, "+2.0", 4));
    EXEC(b = obj.init(NUMBER));
    EXEC(obj.assign(b, "-0.0", 4));

    EXEC(r = calc.lgr(a, b));
    obj.print(r, '\n');

    EXEC(obj.del(a));
    EXEC(obj.del(b));
    EXEC(obj.del(r));


end:
    summarize(__count__, __error__);
    return 0;
}