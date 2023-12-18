#include "felys.h"


ElyObject *
_object_init(ElyType type)
{
    ElyObject * const self = CALLOC(1, ElyObject);
    if (self == NULL) {
        raise(SysError, "<calloc> failed to allocate new memory");
        goto exception;
    }

    self->type = type;
    self->size = 0;
    self->data = NULL;
    self->iter = NULL;
    return self;

exception:
    raise(ObjError, "<_object_init> failed to initialize ElyObject");
    return NULL;
}


bool
_object_assign(ElyObject * const self, char *data, long size)
{
    if (_data_check(self, data, size) == false) {
        goto exception;
    }

    if (_delete_object_data(self) == false) {
        goto exception;
    }

    self->data = CALLOC(size, char);
    if (self->data == NULL) {
        raise(SysError, "<calloc> failed to allocate new memory");
        goto exception;
    }

    self->size = size;
    for (long i=0; i<size; ++i) {
        self->data[i] = data[i];
    }

    return true;

exception:
    raise(ObjError, "<_object_assign> failed to assign the value");
    return false;
}


static bool
_data_check(ElyObject * const self, char *data, long size)
{
    bool result = false;
    if (self->type == NUMBER) {
        result = _number_check(data, size);
    } else if (self->type == STRING) {
        result = _string_check(data, size);
    } else {
        goto exception;
    }

    if (result == false) {
        goto exception;
    }

    return true;

exception:
    raise(ObjError, "<_data_check> data check does not pass");
    return false;
}


static bool
_number_check(char *data, long size)
{
    if (size < 4) {
        raise(ObjError, "<_number_check> number require size > 4");
        goto exception;
    } else if (data[0]!='+' && data[0]!='-') {
        raise(ObjError, "<_number_check> sign is not identified");
        goto exception;
    } else if (data[1]=='.' || data[size-1]=='.') {
        raise(ObjError, "<_number_check> invalid decimal point");
        goto exception;
    }

    bool decimal = false;
    for (long i=1, temp; i<size; ++i) {
        temp = _char_to_int(data[i]);
        if (temp == 10) {
            goto exception;
        } else if (temp == '.') {
            decimal = true;
        }
    }

    if (decimal != true) {
        raise(ObjError, "<_number_check> less or more than one decimal point");
        goto exception;
    }

    return true;

exception:
    return false;
}


static bool
_string_check(char *data, long size)
{
    if (size < 1) {
        raise(ObjError, "<_string_check> string requires size > 1");
        goto exception;
    }

    return true;

exception:
    return false;
}


bool
_object_store(ElyObject * const self, ElyObject **iter, long size)
{
    if (_iter_check(self, size) == false) {
        goto exception;
    }

    if (_delete_object_iter(self) == false) {
        goto exception;
    }

    self->iter = CALLOC(size, ElyObject *);
    if (self->iter==NULL) {
        raise(SysError, "<calloc> failed to allocate new memory");
        goto exception;
    }

    self->size = size;
    for (long i=0; i<size; ++i) {
        self->iter[i] = iter[i];
    }

    return true;

exception:
    raise(ObjError, "<_object_store> failed to store the iterables");
    return false;
}


static bool
_iter_check(ElyObject * const self, long size)
{
    if (self->type != ITERABLE) {
        raise(ObjError, "<_iter_check> invalid data type for store operation");
        goto exception;
    } else if (size < 1) {
        raise(ObjError, "<_iter_check> iterable requires size > 1");
        goto exception;
    }

    return true;

exception:
    return false;
}


bool
_object_delete(ElyObject * const self)
{
    bool result = false;
    if (self->data && self->iter==NULL) {
        result = _delete_object_data(self);
    } else if (self->iter && self->data==NULL) {
        result = _delete_object_iter(self);
    } else {
        goto exception;
    }

    if (result == false) {
        goto exception;
    }

    FREE(self);
    return true;

exception:
    raise(DelError, "<_object_delete> failed to delete object");
    return false;
}


static bool 
_delete_object_data(ElyObject * const self)
{
    FREE(self->data);
    return true;
}


static bool 
_delete_object_iter(ElyObject * const self)
{
    for (long i=0; i<self->size; ++i) {
        bool result = _object_delete(self->iter[i]);
        if (result == false) {
            goto exception;
        }
    }

    FREE(self->iter);
    return true;

exception:
    raise(DelError, "<_delete_object_iter> failed to delete iterables");
    return false;
}


void
_object_print(ElyObject * const self, char end)
{
    if (self->data) {
        _print_data(self);
    } else if (self->iter) {
        _print_iter(self);
    } else {
        printf("NONE");
    }
    putchar(end);
}


static void
_print_data(ElyObject * const self)
{
    long i = (self->type==NUMBER && self->data[0]=='+');
    while (i < self->size) {
        putchar(self->data[i++]);
    }
}


static void
_print_iter(ElyObject * const self)
{
    putchar('[');
    for (long i=0; i<self->size; ++i) {
        putchar(' ');
        _object_print(self->iter[i], '\0');
        putchar(' ');
    }
    putchar(']');
}