#include <stdio.h>
#define MAX 256
#define LEN 8

// float,int,char can be converted automatically
typedef struct{
    float body[MAX];
    int top;
}stack;

int main(void);
void init(stack *);
void push(stack *, float);
float pop(stack *);
int type(char);


int main(void){
    stack oprts; init(&oprts);
    char *expr = "1.1+1-4*5/1+(4-1*9/1+9*8/1+0)";
    char rpn[MAX][LEN] = {0};
    int row = 0;
    int level;

    // convert to reverse polish notation
    while (*expr != 0){
        level = type(*expr);
        switch (level){
            case '?':   // skip any unknown character
                expr++;
            case 0:     // read figures
                for (int i=0; !type(*expr); ++i){
                    rpn[row][i] = *expr++;
                }
                ++row;
                break;
            case -1:    // push '(' or clear stack until top reach '('
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
                if (*expr == '-' && (rpn[0][0]==0 || *(expr-1)=='(')){
                    rpn[row++][0] = '0';    // convert '-x' to '0-x'
                }
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

        if (!type(index)){  // read figure including decimals
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

    // print result
    printf("RPolishN: [ ");
    for (int i=0; rpn[i][0]; ++i){
        printf("%s ", rpn[i]);
    }
    printf("] -> %.2f\n", pop(&calc));

    return 0;
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
