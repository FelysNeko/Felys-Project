#include "felys.h"


void
summarize(size_t *count, errors *errstk)
{
    _print_error_free_mem(errstk);
    if (*count) {
        printf(RED("[%zu] MEMORY LEAKS\n"), *count);
    } else {
        printf(GREEN("NO MEMORY LEAKS\n"));
    }
}


char
_size_t_to_char(size_t x)
{
    if (0<=x && x<= 9) {
        return x+48;
    } else {
        goto exception;
    }

exception:
    raise(CvtError, "<_size_t_to_char> failed to convert size_t to char");
    return 10;
}


size_t
_char_to_size_t(char x)
{
    if ('0'<=x && x<='9') {
        return x-48;
    } else if (x == '.') {
        return '.';
    } else {
        goto exception;
    }

exception:
    raise(CvtError, "<_char_to_size_t> cannot convert char to size_t");
    return 10;
}