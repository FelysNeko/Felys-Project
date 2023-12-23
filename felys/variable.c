#include "felys.h"


void
varwrite(lyr *base, char *name, double value)
{
    if (base->next == NULL) {
        error("NoLayerExist", -1);
    }

    for (lyr *layer=base->next; layer!=NULL; layer=layer->next) {
        for (int i=0; layer->body[i].name[0]!=0; ++i) {
            if (strmatch(layer->body[i].name, name)) {
                layer->body[i].value = value;
                return;
            }
        }
    }

    int i = 0;
    for (; base->next->body[i].name[0]!=0; ++i);

    base->next->body[i].value = value;
    for (int c=0; name[c]!=0; ++c) {
        base->next->body[i].name[c] = name[c];
    }
}


double
varget(lyr *base, char *name)
{
    for (lyr *layer=base->next; layer!=NULL; layer=layer->next) {
        for (int i=0; layer->body[i].name[0]!=0; ++i) {
            if (strmatch(layer->body[i].name, name)) {
                return layer->body[i].value;
            }
        }
    }
    error("VarNotFound", -1);
    return 1;
}


void
lyrinit(lyr *base)
{
    base->scope = -1;
    base->next = NULL;
}


void
lyradd(lyr *base)
{
    lyr *layer = (lyr *)malloc(sizeof(lyr));
    for (int i=0; i<MAX; ++i) {
        layer->body[i].name[0] = 0;
    }

    if (base->next == NULL) {
        layer->scope = 0;
    } else{
        layer->scope = base->next->scope+1;
    }
    layer->next = base->next;
    base->next = layer;
}


void
lyrdlt(lyr *base)
{
    if (base->next == NULL) {
        error("EmptyLinkedList", -1);
    }
    lyr *layer = base->next->next;
    free(base->next);
    if (layer != NULL) {
        base->next = layer;
    } else{
        base->next = NULL;
    }
}


void
lyrlist(lyr *base)
{
    for (lyr *layer=base; layer!=NULL; layer=layer->next) {
        printf("[%d]: ", layer->scope);
        if (layer->scope == -1) {
            printf("BASE (NO DATA HERE)\n");
            continue;
        }
        for (int i=0; layer->body[i].name[0]!=0; ++i) {
            printf("<%d>:[%s]:[%f] ", i, layer->body[i].name, layer->body[i].value);
        }
        putchar('\n');
    }
}