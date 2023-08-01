#include <stdio.h>
#include <stdlib.h>

#define MAX 256
#define LEN 64

#define TRUE 1
#define FALSE 0

#define IF "if"
#define ELIF "elif"
#define ELSE "else"
#define WHILE "while"
#define EXIT "exit"
#define GOTO "goto"
#define NONE ""

typedef char container[MAX][LEN];


#ifndef STACLIB
#include "stack.c"
#ifndef FUNCLIB
#include "function.c"
#ifndef PARSLIB
#include "parse.c"
#ifndef VARILIB
#include "variable.c"
#ifndef POSTLIB
#include "postfix.c"
#endif
#endif
#endif
#endif
#endif
