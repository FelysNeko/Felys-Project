# Felys-Interpreter

Felys Interpreter - Exploration in Postfix Notation and C Object Orientation

* [Prototype](#prototype)
* [Current Version](#current-version)
* [Future Features](#future-features)
* [Additional Infomation](#additional-information)

## Prototype
This folder contains the source file of elementary implementation of postfix notation and variable storage. You can compile it by `clang interpreter.c -o felys` and then execute it by `./felys workplace.ely`. You may find a demo in [prototype/workplace.ely](prototype/workplace.ely).

### Operation
* arithmatic: `+` `-` `*` `/`
* brackets: `(` `)`
* decimal: `3.14`

### Syntax
* case sensitive but not space sensitive
* use `=` to assign the value to the variable
* expression without assignment will be print out


## Current Version
Run `make` To compile (using clang) the program and create a temperary folder for `.o` files. You can find this script in my other repo: [Code-Collection](https://github.com/Jhanny-Kin/Code-Collection/blob/main/Make/makefile), modify the top four variables to customize the script. You can execute it by `./felys workplace.ely` or `./felys workplace.ely debug` for debugging output. You may find a heaviside function demo in [felys/workplace.ely](felys/workplace.ely). Here is the [disign explanation(CHN)](https://www.bilibili.com/read/readlist/rl738985).

### Operation
* arithmatic: `+` `-` `*` `/`
* brackets: `(` `)`
* decimal: `3.14`
* negation: `-3`
* comparison: `>` `<` `=`

### Syntax
* case sensitive but not space sensitive
* use `<-` to assign the value to the variable
* Similar to python syntax: strict indetation, no semicolons/brace
* Support keywords: `while` `if` `elif` `goto` `else` `exit` `show`

### Key Designs
```C
typedef struct Layer {
    struct Layer *next;
    int scope;
    var body[MAX];
} lyr;

typedef struct Command {
    struct Command *next;
    struct Command *jump;
    char *expr;
    char *type;
    int index;
    int scope;
} cmd;
```

## Future Features
You also use `make` to compile the program. This only contains some features related to **object orientation**, **error handling**, **memory tracking**, **namespace**, and **string-style number calculation**, meaning that it is not completed. You need to modify the [future/main.c](future/main.c) file and recompile to test those features, then you can run `./felys` to see the output. 

If all the features all implemented, the new interpreter will be dynamic typing and can calculate almost infinitly large numbers. However, as a first-year university student, I really lack in-depth knowledge related to programming language and compiler, so I think it would be a good idea to stop here. I will definitly come back to finish this program in the future, but for now, I have to move on with my school work and co-op. The followings are some **key designs**. Since they are extremely complicated, I won't explain them here.

### ElyObject
```C
typedef struct ElyObject {
    ElyType type;
    size_t size;
    char *data;
    struct ElyObject **iter;
} ElyObject;
```

### Namespace
```C
typedef struct __object__ {
    ElyObject *(*init)(ElyType);
    bool (*assign)(ElyObject *, char *, size_t);
    bool (*store)(ElyObject *, ElyObject **, size_t);
    bool (*del)(ElyObject *);
    void (*print)(ElyObject *, char);
} __object__;

extern __object__ obj;


typedef struct __calculate__ {
    ElyObject *(*add)(ElyObject *, ElyObject *);
    ElyObject *(*sub)(ElyObject *, ElyObject *);
    ElyObject *(*mul)(ElyObject *, ElyObject *);
    ElyObject *(*lgr)(ElyObject *, ElyObject *);
    ElyObject *(*smr)(ElyObject *, ElyObject *);
    ElyObject *(*eql)(ElyObject *, ElyObject *);
} __calculate__;

extern __calculate__ calc;


typedef struct __stack__ {
    bool (*push)(ElyStack *, ElyObject *);
    ElyObject *(*pop)(ElyStack *);
} __stack__;

extern __stack__ stk;
```

### Error Handling
```C
// there is goto chain to handle errors in all functions, so that you can use this macro in main.c
#define EXEC(exec)\
do {\
    if (!(exec)) {\
        printf(">>> "RED(#exec)"\n");\
        goto end;\
    }\
} while (0)

typedef struct ErrorStack {
    ElyError *data[SIZE];
    int top;
} ErrorStack;

extern ErrorStack _errorstack;
extern ErrorStack * const __error__;
```

### Memory Tracking
```C
#define CALLOC(size, type) (type *)calloc(size, sizeof(type)); ++_counter;
#define FREE(ptr) if (ptr!=NULL) { free(ptr); --_counter; }

extern size_t _counter;
extern size_t * const __count__;
```


## Additional Information
The name "felys" is a combination of my two favourite game characters **Pardofelis** and **Elysia** (both from Honkai Impact 3rd).
