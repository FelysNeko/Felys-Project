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
#define SHOW "show"
#define NONE ""


typedef char container[MAX][LEN];

typedef struct{
    char name[LEN];
    double value;
}var;

typedef struct Layer{
    struct Layer *next;
    int scope;
    var body[MAX];
}lyr;

typedef struct Command{
    struct Command *next;
    struct Command *jump;
    char *expr;
    char *type;
    int index;
    int scope;
}cmd;

typedef struct{
    double body[MAX];
    int top;
}stack;


int strlength(char *);
int strmatch(char *, char *);
char *strstrip(char *, char);

static int loadkw(int, char *, char *);
static int tab(char *);
static int empty(char *);
cmd *dtoc(double);
static void cmdcheck(cmd *);
static cmd *cmdread(cmd *, char *, int);
void cmdparse(cmd *, container);
void cmdinit(cmd *);
void cmdlist(cmd *);

static double rpncalc(char *, lyr *);
static void rpnstd(char *, char *);
static void rpncvt(char *, container *);
double rpnexpr(char *expr, lyr *base);
void rpnshow(container);
static int token(char);
static int letter(char);

void error(char *, int);
void stkinit(stack *);
void stkpush(stack *, double);
double stkpop(stack *stk);
double stktop(stack *);
void stkone(stack *, char);

void lyrinit(lyr *);
void lyradd(lyr *);
void lyrdlt(lyr *);
void lyrlist(lyr *);
void varwrite(lyr *, char *, double);
double varget(lyr *, char *);


#include <stdio.h>
#include <stdlib.h>
#include "function.c"
#include "parse.c"
#include "postfix.c"
#include "stack.c"
#include "variable.c"
