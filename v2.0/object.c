#include "felys.h"


ElyObject *
new(ElyType type, size_t *cp)
{
    ElyObject *self = (ElyObject *)calloc(1, sizeof(ElyObject));
    if (self == NULL) {
        return NULL;
    }

    self->type = type;
    self->size = 0;
    self->data = NULL;
    self->iter = NULL;
    ++(*cp);
    return self;
}


bool
assign(ElyObject *self, char *data, size_t size)
{
    if (self->type==NUMBER || self->type==STRING) {
        free(self->data);
        self->data = (char *)calloc(size, sizeof(char));
        if (self->data==NULL || size<1) {
            return false;
        }

        self->size = size;
        for (int i=0; i<size; ++i) {
            self->data[i] = data[i];
        }
        return true;
    } else {
        return false;
    }
}


bool
refer(ElyObject *self, ElyObject **iter, size_t size, size_t *cp)
{
    if (self->type==RATIONAL || self->type==ITERABLE) {
        empty(self, cp);
        self->iter = (ElyObject **)calloc(size, sizeof(ElyObject *));
        if (self->iter==NULL || size<1) {
            return false;
        }

        self->size = size;
        for (int i=0; i<size; ++i) {
            self->iter[i] = iter[i];
        }
        return true;
    } else {
        return false;
    }
}


void
delete(ElyObject *self, size_t *cp)
{
    if (self->data) {
        free(self->data);
    } else if (self->iter) {
        empty(self, cp);
    }
    free(self);
    --(*cp);
}


static void
empty(ElyObject *self, size_t *cp)
{
    for (int i=0; i<self->size; ++i) {
        delete(self->iter[i], cp);
    }
    free(self->iter);
}