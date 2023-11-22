#include "felys.h"


double
rpnexpr(char *expr, lyr *base)
{
    int i = 0;
    for (; expr[i+1]!=0; ++i) {
        if (expr[i]=='<' && expr[i+1]=='-') {
            break;
        }
    }

    int write = FALSE;
    char name[LEN] = {0};
    if (!strmatch(expr, NONE) && strlength(expr)!=i+1) {
        for (int c=0; c<i; ++c) {
            if (expr[c] != ' ') {
                name[c] = expr[c];
            }
        }
        expr = expr+i+2;
        write = TRUE;
    }

    double result = rpncalc(expr, base);
    if (write == TRUE) {
        varwrite(base, name, result);
    }
    
    return result;
}


static double
rpncalc(char *expr, lyr *base)
{
    char stdexpr[LEN] = {0};
    rpnstd(expr, stdexpr);

    container rpn = {0};
    rpncvt(stdexpr, &rpn);

    stack calc; stkinit(&calc);
    double number;
    int index;
    int deci;

    for (int i=0; rpn[i][0]; ++i) {
        index = rpn[i][0];
        number = 0.0;
        deci = 0;

        if (letter(index)) {
            stkpush(&calc, varget(base, rpn[i]));
        }else if (!token(index)) {  
            for (int c=0; rpn[i][c]!=0; c++) {
                if (rpn[i][c] == '.') {
                    deci = 1;
                    continue;
                }
                number = number*10 + rpn[i][c] - 48;
                if (deci) {
                    number /= 10;
                }
            }
            stkpush(&calc, number);
        } else{
            switch (index) {
                case '+': stkpush(&calc, stkpop(&calc)+stkpop(&calc)); break;
                case '-': stkpush(&calc, -stkpop(&calc)+stkpop(&calc)); break;
                case '*': stkpush(&calc, stkpop(&calc)*stkpop(&calc)); break;
                case '/': stkpush(&calc, 1/stkpop(&calc)*stkpop(&calc)); break;
                case '>': stkpush(&calc, stkpop(&calc)<stkpop(&calc)); break;
                case '<': stkpush(&calc, stkpop(&calc)>stkpop(&calc)); break;
                case '=': stkpush(&calc, stkpop(&calc)==stkpop(&calc)); break; 
            }
        }
    }

    return stktop(&calc);
}


void
rpnshow(container rpn)
{
    printf("[ ");
    for (int i=0; rpn[i][0]; ++i) {
        printf("%s ", rpn[i]);
    }
    printf("]\n");
}


static void
rpncvt(char *expr, container *rpn)
{
    stack oprts; stkinit(&oprts);
    int row = 0;

    while (*expr != 0) {
        if (token(*expr) == 0) {
            for (int i=0; !token(*expr); ++i) {
                (*rpn)[row][i] = *expr++;
            }
            ++row;
        } else if (*expr == '(') {
            stkpush(&oprts, *expr++);
        } else if (*expr == ')') {
            while (stktop(&oprts) != '(') {
                (*rpn)[row++][0] = stkpop(&oprts);
            }
            stkpop(&oprts);
            expr++;
        } else{
            while (oprts.top!=-1 && token(stktop(&oprts)) >= token(*expr)) {
                (*rpn)[row++][0] = stkpop(&oprts);
            }
            stkpush(&oprts, *expr++);
        }
    }

    while (oprts.top != -1) {
        (*rpn)[row++][0] = stkpop(&oprts);
    }
}


static void
rpnstd(char *expr, char *target)
{
    char temp[LEN] = {0};
    for (int i=0; *expr!=0; expr++) {
        if (token(*expr)!='?') {
            temp[i++] = *expr;
        } else if (*expr == ' ') {
            continue;
        } else{
            error("UnknownCharacter", -1);
        }
    }

    stack brackets; stkinit(&brackets);
    expr = temp;

    for (int i=0; *expr!=0; expr++) {
        if (token(*expr)==2 && (target[0]==0 || *(expr-1)=='(' || token(*(expr-1))>0)) {
            target[i++] = '('; target[i++] = '0';
            stkone(&brackets, '+');
            stkpush(&brackets, 0);
        } else if (token(*expr) == -1) {
            switch (*expr) {
                case '(': stkone(&brackets, '+'); break;
                case ')': stkone(&brackets, '-'); break;
            }
        }
        target[i++] = *expr;
        if (*expr==')' || *(expr+1)==0 || (!token(*expr) && token(*(expr+1)))) {
            while (brackets.body[brackets.top]==0 && brackets.top!=-1) {
                target[i++] = ')';
                stkone(&brackets, '-');
                stkpop(&brackets);
            }
        }
    }
}


static int
token(char c)
{
    if (('0'<=c && c<='9') || c=='.' || letter(c)) {
        return 0;
    } else if (c=='(' || c==')') {
        return -1;
    } else if (c=='*' || c=='/') {
        return 3;
    } else if (c=='+' || c=='-') {
        return 2;
    } else if (c=='>' || c=='=' || c=='<') {
        return 1;
    } else{
        return '?';
    }
}


static int
letter(char c)
{
    return ('a'<=c && c<='z') || ('A'<=c && c<='Z') ? 1 : 0;
}
