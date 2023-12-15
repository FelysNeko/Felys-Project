#include "felys.h"

int main(void)
{
    ElyObject *x = obj.init(NUMBER);
    obj.assign(x, "+123.a", 6);

    obj.del(x);

end:
    summarize(__count__, __error__);
    return 0;
}