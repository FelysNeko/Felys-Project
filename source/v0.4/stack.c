#define STACLIB
#include "header.h"

typedef struct{
    double body[MAX];
    int top;
}stack;


void error(char *, int);
void stkinit(stack *);
void stkpush(stack *, double);
double stktop(stack *);
void stkone(stack *, char);


void error(char *msg, int index){
    if (index == -1){
        printf("[%s]\n", msg);
    } else{
        printf("[%s] at line[%d]\n", msg, index);
    }
    exit(1);
}


void stkinit(stack *skt){
    skt->top = -1;
}


void stkpush(stack *stk, double value){
    if (stk->top == MAX-1){
        error("StackOverflow", -1);
    }
    stk->body[++stk->top] = value;
}


double stkpop(stack *stk){
    if (stk->top == -1){
        error("EmptyStack", -1);
    }
    return stk->body[stk->top--];
}


double stktop(stack *stk){
    return stk->top>-1 ? stk->body[stk->top] : 0;
}


void stkone(stack *stk, char o){
    // full stack plus one or minus one
    for (int i=0; i<stk->top+1; ++i){
        switch (o){
            case '+': ++stk->body[i]; break;
            case '-': --stk->body[i]; break;
            default: break;
        }  
    }
}