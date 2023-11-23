#include "define.h"
#include "typedef.h"

#ifndef __FUNCTION_H
#define __FUNCTION_H

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
cmd *cmdgoto(cmd *, int);

static double rpncalc(char *, lyr *);
static void rpnstd(char *, char *);
static void rpncvt(char *, container *);
double rpnexpr(char *, lyr *);
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

#endif