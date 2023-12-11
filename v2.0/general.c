#include "felys.h"

void
raise(char *msg)
{
    printf("ERROR: %s\n", msg);
    exit(1);
}

int
char_to_int(char c)
{
    if (c<'0' || '9'<c) {
        raise("unable to convert char to int");
    }
    return c-48;
}


char
int_to_char(int i)
{
    if (i<0 || 9<i) {
        raise("unable to convert int to char");
    }
    return i+48;
}