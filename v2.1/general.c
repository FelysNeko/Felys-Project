#include "felys.h"


void
summarize(long *count, errors *errstk)
{
    _print_error_free_mem(errstk);
    if (*count) {
        printf(RED("[%zu] MEMORY LEAKS\n"), *count);
    } else {
        printf(GREEN("NO MEMORY LEAKS\n"));
    }
}


char
_int_to_char(int x)
{
    if (0<=x && x<= 9) {
        return x+48;
    } else {
        goto exception;
    }

exception:
    raise(CvtError, "<_int_to_char> failed to convert int to char");
    return 10;
}


int
_char_to_int(char x)
{
    if ('0'<=x && x<='9') {
        return x-48;
    } else if (x == '.') {
        return '.';
    } else {
        goto exception;
    }

exception:
    raise(CvtError, "<_char_to_int> cannot convert char to int");
    return 10;
}