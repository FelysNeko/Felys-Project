#include <stdio.h>
#include <stdlib.h>
#define MAX 256
#define LEN 8

typedef struct{
    char body[MAX];
    int top;
}cstack;

//this is a supid float stack, exact same as type 'cstack' except it stores float
typedef struct{
    float body[MAX];
    int top;
}fstack;


int main(void);
int type(char);
// c for char stack function
void cinit(cstack *);
void cpush(cstack *, char);
char cpop(cstack *);
// f for float stack funtion
void finit(fstack *);
void fpush(fstack *, float);
float fpop(fstack *);


int main(void){
    char *expr = "1.1+1-4*5/1+(4-1*9/1+9*8/1+0)";
    printf("Original: [ %s ]\n", expr);

    cstack oprts;
    cinit(&oprts);
    char rpn[MAX][LEN] = {0};
    int row = 0;
    int level;
    
    while (*expr != 0){
        // skip space
        if(*expr==' '){
            expr++;
            continue;;
        }

        level = type(*expr);
        switch (level){
            case 0:
                // output figures directly 
                for (int i=0; !type(*expr); ++i){
                    rpn[row][i] = *expr++;
                }
                ++row;
                break;
            
            case -1:
                // cpush all '('
                if (*expr == '('){
                    cpush(&oprts, *expr++);
                // cpop out all the operation signs until cstack top reaches the closest '('
                } else{
                    while (oprts.body[oprts.top] != '('){
                        rpn[row++][0] = cpop(&oprts);
                    }
                    cpop(&oprts);
                    expr++;
                }
                break;

            default:
                // convert "-x" to "0-x"
                if (*expr == '-' && (rpn[0][0]==0 || *(expr-1)=='(')){
                    rpn[row++][0] = '0';
                }
                // cpop out all the operation signs until it clear out cstack or find a sign that is less prior
                while (oprts.top!=-1 && type(oprts.body[oprts.top]) >= level){
                    rpn[row++][0] = cpop(&oprts);
                }
                cpush(&oprts, *expr++);
                break;
        }
    }

    while (oprts.top != -1){
        rpn[row++][0] = cpop(&oprts);
    }
    
    printf("RPolishN: [ ");
    for (int i=0; rpn[i][0]; ++i){
        printf("%s ", rpn[i]);
    }
    putchar(']');


    fstack calc;
    finit(&calc);
    float number;
    int index;
    int deci;

    for (int i=0; rpn[i][0]; ++i){
        index = rpn[i][0];
        number = 0.0;

        if (!type(index)){
            deci = 0;
            // read figure include decimals
            for (int c=0; rpn[i][c]!=0; c++){
                if (rpn[i][c] == '.'){
                    deci = 1; continue;
                }
                number = number*10 + rpn[i][c] - 48;
                if (deci) number /= 10;
            }
            fpush(&calc, number);
            
        } else{
            // calculations, some math manipulations for subtraction and division
            switch (index){
                case '+': fpush(&calc, fpop(&calc)+fpop(&calc)); break;
                case '-': fpush(&calc, -fpop(&calc)+fpop(&calc)); break;
                case '*': fpush(&calc, fpop(&calc)*fpop(&calc)); break;
                case '/': fpush(&calc, 1/fpop(&calc)*fpop(&calc)); break;
            }
        }
    }

    printf(" -> %.2f\n", fpop(&calc));
    return 0;
}

// functions
void cinit(cstack *skt){
    skt->top = -1;
}
void finit(fstack *skt){
    skt->top = -1;
}


void cpush(cstack *stk, char value){
    stk->body[++stk->top] = value;
}
void fpush(fstack *stk, float value){
    stk->body[++stk->top] = value;
}


// cpop only make user overwrite it through cpush
// do not manipulate stk.top anywhere
char cpop(cstack *stk){
    return stk->body[stk->top--];
}
float fpop(fstack *stk){
    return stk->body[stk->top--];
}


int type(char c){
    if (('0'<=c && c<='9') || c=='.'){
        return 0;
    } else if (c=='*' || c=='/'){
        return 2;
    } else if (c=='+' || c=='-'){
        return 1;
    } else{
        return -1;
    }
}
