#include "felys.h"


void
summarize(size_t *count, error *errstk)
{
    _print_error_free_mem(errstk);
    if (*count) {
        printf(RED("[%zu] MEMORY LEAKS"), *count);
    } else {
        printf(GREEN("NO MEMORY LEAKS"));
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
    raise(ConvertError, "cannot convert int to char");
    return -1;
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
    raise(ConvertError, "cannot convert char to int");
    return -1;
}