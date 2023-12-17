#ifndef __DEFINE_H__
#define __DEFINE_H__


#define SIZE 256

#define CALLOC(size, type) (type *)calloc(size, sizeof(type)); ++_counter;
#define FREE(ptr) if (ptr!=NULL) { free(ptr); --_counter; }
#define EXEC(exec) do { if (!(exec)) goto end; } while (0)
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define RED(msg) "\033[1;31m"msg"\033[0m\n"
#define GREEN(msg) "\033[1;32m"msg"\033[0m\n"

extern long _counter;
extern long * const __count__;


#endif