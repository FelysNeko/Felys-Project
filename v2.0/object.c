#include "felys.h"


ElyObject *
obj_new(ElyType type, size_t *cp)
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
obj_assign(ElyObject *self, char *data, size_t size)
{
    if (self->type==NUMBER || self->type==STRING) {
        obj_data_delete(self);
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
obj_refer(ElyObject *self, ElyObject **iter, size_t size, size_t *cp)
{
    if (self->type==RATIONAL || self->type==ITERABLE) {
        obj_iter_delete(self, cp);
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
obj_delete(ElyObject *self, size_t *cp)
{
    if (self->data) {
        obj_data_delete(self);
    } else if (self->iter) {
        obj_iter_delete(self, cp);
    }
    free(self);
    --(*cp);
}


static void
obj_iter_delete(ElyObject *self, size_t *cp)
{
    for (int i=0; i<self->size; ++i) {
        obj_delete(self->iter[i], cp);
    }
    free(self->iter);
}


static void
obj_data_delete(ElyObject *self)
{
    free(self->data);
}


void
obj_print(ElyObject *self, char end)
{
    if (self->data) {
        obj_data_print(self);
    } else if (self->iter) {
        obj_iter_print(self);
    } else {
        printf("NONE");
    }
    putchar(end);
}


static void
obj_data_print(ElyObject *self)
{
    for (int i=0; i<self->size; ++i) {
        putchar(self->data[i]);
    }
}


static void
obj_iter_print(ElyObject *self)
{
    putchar('[');
    for (int i=0; i<self->size; ++i) {
        putchar(' ');
        obj_print(self->iter[i], '\0');
        putchar(' ');
    }
    putchar(']');
}