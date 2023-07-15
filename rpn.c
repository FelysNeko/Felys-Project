#include <stdio.h>
#define MAX 256
#define LEN 8

// float,int,char can be converted automatically
typedef struct{
    float body[MAX];
    int top;
}stack;

float rpn(char *);
void init(stack *);
void push(stack *, float);
float pop(stack *);
int type(char);
void one(stack *, char);    // char is either '+' or '-'
float rpn(char *);


int main(void){
    printf("Result: \t%f\n", rpn("1/-2-1"));
    return 0;
}


float rpn(char *expr){
    stack brackets; init(&brackets);
    char temp[MAX] = {0};

    for (int i=0; *expr!=0; expr++){
        // appened "(0" and push a counter into the brackets stack
        if (type(*expr)==1 && (temp[0]==0 || *(expr-1)=='(' || type(*(expr-1))>0)){
            temp[i++] = '('; temp[i++] = '0';
            one(&brackets, '+');
            push(&brackets, 0);
        // when it reads a bracket
        } else if (type(*expr) == -1){
            switch (*expr){
                case '(': one(&brackets, '+'); break;
                case ')': one(&brackets, '-'); break;
            }
        }
        temp[i++] = *expr;
        // three cases to pop add a close bracket
        if (*expr==')' || *(expr+1)==0 || (!type(*expr) && type(*(expr+1)))){
            // clear out the close bracket thats are ready to go
            while (brackets.body[brackets.top]==0 && brackets.top!=-1){
                temp[i++] = ')';
                one(&brackets, '-');
                pop(&brackets);
            }
        }
    }

    stack oprts; init(&oprts);
    char rpn[MAX][LEN] = {0};
    expr = temp;
    int row = 0;
    int level;

    // convert to reverse polish notation
    while (*expr != 0){
        level = type(*expr);
        switch (level){
            case '?':   // skip any unknown character
                expr++;
                break;
            case 0:     // read figures
                for (int i=0; !type(*expr); ++i){
                    rpn[row][i] = *expr++;
                }
                ++row;
                break;
            case -1:    // push '(' or clear stack until top reach ')'
                if (*expr == '('){
                    push(&oprts, *expr++);
                } else{
                    while (oprts.body[oprts.top] != '('){
                        rpn[row++][0] = pop(&oprts);
                    }
                    pop(&oprts);
                    expr++;
                }
                break;
            default:    // case 2&3: clear stack until top is less prior than current sign, and push itself
                while (oprts.top!=-1 && type(oprts.body[oprts.top]) >= level){
                    rpn[row++][0] = pop(&oprts);
                }
                push(&oprts, *expr++);
                break;
        }
    }

    // output remainings in stack
    while (oprts.top != -1){
        rpn[row++][0] = pop(&oprts);
    }

    stack calc; init(&calc);
    float number;
    int index;
    int deci;

    // calculation
    for (int i=0; rpn[i][0]; ++i){
        index = rpn[i][0];
        number = 0.0;
        deci = 0;

        if (!type(index)){  // read figure include decimals
            for (int c=0; rpn[i][c]!=0; c++){
                if (rpn[i][c] == '.'){
                    deci = 1; continue;
                }
                number = number*10 + rpn[i][c] - 48;
                if (deci) number /= 10;
            }
            push(&calc, number);
        } else{
            // basic calculations with some math manipulations for subtraction and division
            switch (index){
                case '+': push(&calc, pop(&calc)+pop(&calc)); break;
                case '-': push(&calc, -pop(&calc)+pop(&calc)); break;
                case '*': push(&calc, pop(&calc)*pop(&calc)); break;
                case '/': push(&calc, 1/pop(&calc)*pop(&calc)); break;
            }
        }
    }

    printf("Rewritte: \t[ %s ]\n", temp);
    printf("RPolishN: \t[ ");
    for (int i=0; rpn[i][0]; ++i){
        printf("%s ", rpn[i]);
    }
    printf("]\n");

    return pop(&calc);
}

void init(stack *skt){
    skt->top = -1;
}

void push(stack *stk, float value){
    stk->body[++stk->top] = value;
}

float pop(stack *stk){
    return stk->body[stk->top--];
}

void one(stack *stk, char o){
    for (int i=0; i<stk->top+1; ++i){
        switch (o){
            case '+': ++stk->body[i]; break;
            case '-': --stk->body[i]; break;
            default: break;
        }  
    }
}

int type(char c){
    if (('0'<=c && c<='9') || c=='.'){
        return 0;
    } else if (c=='*' || c=='/'){
        return 2;
    } else if (c=='+' || c=='-'){
        return 1;
    } else if(c=='(' || c==')'){
        return -1;
    }else{
        return '?';
    }
}
