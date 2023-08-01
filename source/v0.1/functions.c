#define MAX 256
#define LEN 16

// float,int,char will be converted automatically
typedef struct{
    float body[MAX];
    int top;
}stack;

typedef struct{
    char name[LEN];
    float figure;
}var;

typedef struct{
    var body[MAX];
    int count;
}variables;


typedef char rpn[MAX][LEN];

void init(stack *);
void push(stack *, float);
float pop(stack *);
void one(stack *, char);    // char is either '+' or '-'

void initrpn(rpn *);
void postfix(rpn *, char *);
void showrpn(rpn);

int type(char);
int isletter(char);

void initvar(variables *);
void addvar(variables *, char *, float);
float findvar(variables, char *);

float calculate(rpn, variables);


void postfix(rpn *container, char *expr){
    // get rid of any unknown character
    char nospace[MAX] = {0};
    for (int i=0; *expr!=0; ){
        if (type(*expr) != '?'){
            nospace[i++] = *expr;
        }
        ++expr;
    }

    stack brackets; init(&brackets);
    char temp[MAX] = {0};
    expr = nospace;

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
    expr = temp;
    int row = 0;
    int level;

    // convert to reverse polish notation
    while (*expr != 0){
        level = type(*expr);
        switch (level){
            case 0:     // read figures
                for (int i=0; !type(*expr); ++i){
                    (*container)[row][i] = *expr++;
                }
                ++row;
                break;
            case -1:    // push '(' or clear stack until top reach ')'
                if (*expr == '('){
                    push(&oprts, *expr++);
                } else{
                    while (oprts.body[oprts.top] != '('){
                        (*container)[row++][0] = pop(&oprts);
                    }
                    pop(&oprts);
                    expr++;
                }
                break;
            default:    // case 2&3: clear stack until top is less prior than current sign, and push itself
                while (oprts.top!=-1 && type(oprts.body[oprts.top]) >= level){
                    (*container)[row++][0] = pop(&oprts);
                }
                push(&oprts, *expr++);
                break;
        }
    }

    // output remainings in stack
    while (oprts.top != -1){
        (*container)[row++][0] = pop(&oprts);
    }
}


void showrpn(rpn container){
    printf("[ ");
    for (int i=0; container[i][0]; ++i){
        printf("%s ", container[i]);
    }
    printf("]\n");
}


void initrpn(rpn *container){
    for (int row=0; row<MAX; ++row){
        for (int col=0; col<LEN; ++col){
            (*container)[row][col] = 0;
        }
    }
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
    // full stack plus one or minus one
    for (int i=0; i<stk->top+1; ++i){
        switch (o){
            case '+': ++stk->body[i]; break;
            case '-': --stk->body[i]; break;
            default: break;
        }  
    }
}


int isletter(char c){
    return ('a'<=c && c<='z') || ('A'<=c && c<='Z') ? 1 : 0;
}


int type(char c){
    if (('0'<=c && c<='9') || c=='.' || isletter(c)){
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


void initvar(variables *data){
    data->count = 0;
}


void addvar(variables *data, char *name, float figure){
    int match;
    int c = 0;
    int i;

    for (match=1; c < data->count; ++c){
        for (i=0; name[i]!=0; ++i){
            if (data->body[c].name[i] != name[i]){
                match = 0; break;
            }
        }
        if (match && i<LEN && data->body[c].name[i+1]!=0) break;
    }

    if (match && data->count){
        // rewrite if var already exist
        data->body[c].figure = figure;
    } else{
        // add new var with name and data
        for (int i=0; name[i]!=0; ++i){
            data->body[data->count].name[i] = name[i];
        }
        data->body[data->count++].figure = figure;
    }
}


float findvar(variables data, char *name){
    int match;
    int i;
    for (int c=0; c<data.count; ++c){
        match = 1;
        for (i=0; name[i]!=0; ++i){
            if (data.body[c].name[i] != name[i]){
                match = 0; break;
            }
        }
        if (match && i<LEN && data.body[c].name[i+1]!=0){
            return data.body[c].figure;
        }
    }
    printf("[%s] not found, default using 0\n", name);
    return 0;
}


float calculate(rpn container, variables data){
    stack calc; init(&calc);
    float number;
    int index;
    int deci;

    // calculation
    for (int i=0; container[i][0]; ++i){
        index = container[i][0];
        number = 0.0;
        deci = 0;

        if (isletter(index)){
            push(&calc, findvar(data, container[i]));
        }else if (!type(index)){  
            // read figures including decimals
            for (int c=0; container[i][c]!=0; c++){
                if (container[i][c] == '.'){
                    deci = 1; continue;
                }
                number = number*10 + container[i][c] - 48;
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

    return pop(&calc);
}
