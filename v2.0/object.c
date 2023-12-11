#include "felys.h"


ElyObject *
obj_new(ElyType type, size_t *cp)
{
    ElyObject * const self = (ElyObject *)calloc(1, sizeof(ElyObject));
    if (self == NULL) {
        goto error;
    }

    self->type = type;
    self->size = 0;
    self->data = NULL;
    self->iter = NULL;
    ++(*cp);
    return self;

error: 
    raise("cannot allocate a new object");
    return NULL;
}


void
obj_assign(ElyObject * const self, char *data, size_t size)
{
    if (self->type!=INTEGER && self->type!=DECIMAL && self->type!=STRING) {
        goto error;
    }

    obj_data_delete(self);
    self->data = (char *)calloc(size, sizeof(char));
    if (self->data==NULL || size<1) {
        goto error;
    }

    self->size = size;
    for (int i=0; i<size; ++i) {
        self->data[i] = data[i];
    }
    
    return;

error:
    raise("cannot assign the value");
}


void
obj_refer(ElyObject * const self, ElyObject **iter, size_t size, size_t *cp)
{
    if (self->type!=ITERABLE) {
        goto error;
    }

    obj_iter_delete(self, cp);
    self->iter = (ElyObject **)calloc(size, sizeof(ElyObject *));
    if (self->iter==NULL || size<1) {
        goto error;
    }

    self->size = size;
    for (int i=0; i<size; ++i) {
        self->iter[i] = iter[i];
    }

    return;

error:
    raise("cannot refer the iterable");
}


void
obj_delete(ElyObject * const self, size_t *cp)
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
obj_iter_delete(ElyObject * const self, size_t *cp)
{
    for (int i=0; i<self->size; ++i) {
        obj_delete(self->iter[i], cp);
    }
    free(self->iter);
}


static void
obj_data_delete(ElyObject * const self)
{
    free(self->data);
}


void
obj_print(ElyObject * const self, char end)
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
obj_data_print(ElyObject * const self)
{
    for (int i=0; i<self->size; ++i) {
        putchar(self->data[i]);
    }
}


static void
obj_iter_print(ElyObject * const self)
{
    putchar('[');
    for (int i=0; i<self->size; ++i) {
        putchar(' ');
        obj_print(self->iter[i], '\0');
        putchar(' ');
    }
    putchar(']');
}