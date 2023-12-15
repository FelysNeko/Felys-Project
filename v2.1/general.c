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