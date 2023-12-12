#ifndef __GENERAL_H__
#define __GENERAL_H__


#define CALLOC(size, type) (type *)calloc(size, sizeof(type)); ++counter;
#define FREE(ptr) if (ptr!=NULL) {free(ptr); --counter;}

#define RED(msg) "\033[1;31m"msg"\033[0m\n"
#define GREEN(msg) "\033[1;32m"msg"\033[0m\n"


void raise(char *);
int char_to_int(char);
char int_to_char(int);
void summarize(size_t);


#endif