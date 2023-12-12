#include "felys.h"


ElyObject *
obj_new(ElyType type)
{
    ElyObject * const self = CALLOC(1, ElyObject);
    if (self == NULL) {
        goto error;
    }

    self->type = type;
    self->size = 0;
    self->data = NULL;
    self->iter = NULL;
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

    _obj_data_delete(self);
    self->data = CALLOC(size, char);
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
obj_refer(ElyObject * const self, ElyObject **iter, size_t size)
{
    if (self->type!=ITERABLE) {
        goto error;
    }

    _obj_iter_delete(self);
    self->iter = CALLOC(size, ElyObject *);
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
obj_delete(ElyObject * const self)
{
    if (self->data) {
        _obj_data_delete(self);
    } else if (self->iter) {
        _obj_iter_delete(self);
    }
    FREE(self);
}


static void
_obj_iter_delete(ElyObject * const self)
{
    for (int i=0; i<self->size; ++i) {
        obj_delete(self->iter[i]);
    }
    FREE(self->iter);
}


static void
_obj_data_delete(ElyObject * const self)
{
    FREE(self->data);
}


void
obj_print(ElyObject * const self, char end)
{
    if (self->data) {
        _obj_data_print(self);
    } else if (self->iter) {
        _obj_iter_print(self);
    } else {
        printf("NONE");
    }
    putchar(end);
}


static void
_obj_data_print(ElyObject * const self)
{   
    int i = ((self->type==INTEGER || self->type==DECIMAL) && self->data[0]=='+');
    while (i < self->size) {
        putchar(self->data[i++]);
    }
}


static void
_obj_iter_print(ElyObject * const self)
{
    putchar('[');
    for (int i=0; i<self->size; ++i) {
        putchar(' ');
        obj_print(self->iter[i], '\0');
        putchar(' ');
    }
    putchar(']');
}