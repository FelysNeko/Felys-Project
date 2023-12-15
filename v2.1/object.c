#include "felys.h"


ElyObject *
_object_init(ElyType type)
{
    ElyObject * const self = CALLOC(1, ElyObject);
    if (self == NULL) {
        raise(SystemError, "cannot allocation new memory");
        goto exception;
    }

    self->type = type;
    self->size = 0;
    self->data = NULL;
    self->iter = NULL;
    return self;

exception:
    raise(ObjectError, "failed to initialize object");
    return NULL;
}


bool
_object_assign(ElyObject * const self, char *data, size_t size)
{
    if (_data_check(self, data, size) == false) {
        goto exception;
    }

    if (_delete_object_data(self) == false) {
        raise(ObjectError, "unable to clear original container");
        goto exception;
    }

    self->data = CALLOC(size, char);
    if (self->data == NULL) {
        raise(SystemError, "cannot allocation new memory");
        goto exception;
    }

    self->size = size;
    for (int i=0; i<size; ++i) {
        self->data[i] = data[i];
    }

    return true;

exception:
    raise(ObjectError, "cannot assign the value");
    return false;
}


static bool
_data_check(ElyObject * const self, char *data, size_t size)
{
    bool result = false;
    if (self->type == NUMBER) {
        result = _number_check(data, size);
    } else if (self->type == STRING) {
        result = _string_check(data, size);
    } else {
        raise(ObjectError, "invalid data typefor assign operation");
        goto exception;
    }

    if (result == false) {
        goto exception;
    }

    return true;

exception:
    raise(ObjectError, "data check does not pass");
    return false;
}


static bool
_number_check(char *data, size_t size)
{
    if (size < 4) {
        raise(ObjectError, "number should have length more than 4, i.e. +0.0");
        goto exception;
    } else if (data[0]!='+' && data[0]!='-') {
        raise(ObjectError, "sign is not identified");
        goto exception;
    } else if (data[1]=='.' || data[size-1]=='.') {
        raise(ObjectError, "invalid decimal point");
        goto exception;
    }

    bool decimal = false;
    for (int i=1, temp; i<size; ++i) {
        temp = _char_to_int(data[i]);
        if (temp == -1) {
            goto exception;
        } else if (temp == '.') {
            decimal = true;
        }
    }

    if (decimal != true) {
        raise(ObjectError, "number of decimal point should be one");
        goto exception;
    }

    return true;

exception:
    raise(ObjectError, "number check does not pass");
    return false;
}


static bool
_string_check(char *data, size_t size)
{
    if (size < 1) {
        raise(ObjectError, "string must have length more than one");
        goto exception;
    }

    return true;

exception:
    raise(ObjectError, "string check does not pass");
    return false;
}


bool
_object_store(ElyObject * const self, ElyObject **iter, size_t size)
{
    if (_iter_check(self, size) == false) {
        goto exception;
    }

    if (_delete_object_iter(self) == false) {
        raise(ObjectError, "unable to clear original container");
        goto exception;
    }

    self->iter = CALLOC(size, ElyObject *);
    if (self->iter==NULL) {
        raise(SystemError, "cannot allocation new memory");
        goto exception;
    }

    self->size = size;
    for (int i=0; i<size; ++i) {
        self->iter[i] = iter[i];
    }

    return true;

exception:
    raise(ObjectError, "unable to store the iterables");
    return false;
}


static bool
_iter_check(ElyObject * const self, size_t size)
{
    if (self->type != ITERABLE) {
        raise(ObjectError, "invalid data typefor store operation");
        goto exception;
    } else if (size < 1) {
        raise(ObjectError, "iterable must have more than one value");
        goto exception;
    }

    return true;

exception:
    raise(ObjectError, "iter check does not pass");
    return false;
}


bool
_object_delete(ElyObject * const self)
{
    if (self == NULL) {
        raise(DeleteError, "trying to free an NULL pointer");
        goto exception;
    }

    bool result = false;
    if (self->data && self->iter==NULL) {
        result = _delete_object_data(self);
    } else if (self->iter && self->data==NULL) {
        result = _delete_object_iter(self);
    } else {
        raise(DeleteError, "trying to free an skeleton or invalid object");
        goto exception;
    }

    if (result == false) {
        goto exception;
    }

    FREE(self);
    return true;

exception:
    raise(DeleteError, "unable to free object");
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
    for (int i=0; i<self->size; ++i) {
        bool result = _object_delete(self->iter[i]);
        if (result == false) {
            goto exception;
        }
    }

    FREE(self->iter);
    return true;

exception:
    raise(DeleteError, "failed to delete object iterables");
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
    int i = (self->type==NUMBER && self->data[0]=='+');
    while (i < self->size) {
        putchar(self->data[i++]);
    }
}


static void
_print_iter(ElyObject * const self)
{
    putchar('[');
    for (int i=0; i<self->size; ++i) {
        putchar(' ');
        _object_print(self->iter[i], '\0');
        putchar(' ');
    }
    putchar(']');
}