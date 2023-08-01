#define VARILIB
#include "header.h"


typedef struct{
    char name[LEN];
    double value;
}var;

typedef struct Layer{
    struct Layer *next;
    int scope;
    var body[MAX];
}lyr;


void lyrinit(lyr *);
void lyradd(lyr *);
void lyrdlt(lyr *);
void lyrlist(lyr *);

void varwrite(lyr *, char *, double);
double varget(lyr *, char *);


void varwrite(lyr *base, char *name, double value){
    lyr *line = base;
    if (base == NULL){
        error("NoLayerExist", -1);
    }

    for (; line!=NULL; line=line->next){
        for (int i=0; line->body[i].name[0]!=0; ++i){
            if (strmatch(line->body[i].name, name)){
                line->body[i].value = value;
                return;
            }
        }
    }

    int i = 0;
    for (; base->body[i].name[0]!=0; ++i);
    base->body[i].value = value;
    for (int c=0; name[c]!=0; ++c){
        base->body[i].name[c] = name[c];
    }
}


double varget(lyr *base, char *name){
    for (; base!=NULL; base=base->next){
        for (int i=0; base->body[i].name[0]!=0; ++i){
            if (strmatch(base->body[i].name, name)){
                return base->body[i].value;
            }
        }
    }
    error("VarNotFound", -1);
    return 1;
}


void lyrinit(lyr *base){
    base->scope = -1;
    base->next = NULL;
}


void lyradd(lyr *base){
    lyr *crnt = (lyr *)malloc(sizeof(lyr));
    for (int i=0; i<MAX; ++i){
        crnt->body[i].name[0] = 0;
    }

    if (base->next == NULL){
        crnt->scope = 0;
    } else{
        crnt->scope = base->next->scope+1;
    }
    crnt->next = base->next;
    base->next = crnt;
}


void lyrdlt(lyr *base){
    if (base->next == NULL){
        error("EmptyLinkedList", -1);
    }
    lyr *new = base->next->next;
    free(base->next);
    if (new != NULL){
        base->next = new;
    } else{
        base->next = NULL;
    }
}


void lyrlist(lyr *crnt){
    for (; crnt!=NULL; crnt=crnt->next){
        printf("[%d]: ", crnt->scope);
        if (crnt->scope == -1){
            printf("BASE (NO DATA HERE)\n");
            continue;
        }
        for (int i=0; crnt->body[i].name[0]!=0; ++i){
            printf("<%d>:[%s]:[%f] ", i, crnt->body[i].name, crnt->body[i].value);
        }
        putchar('\n');
    }
}