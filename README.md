# Felys-Project

This is the playground to test components of real Felys-Interpreter. Note that the AST parser is a standalone cli program. The reason why I put it here is that the project will move to Rust in the future.

- [Prototype [C]](#prototype)
- [Current Version [C]](#current-version)
- [Future Features [C]](#future-features)
- [AST Parser [Rust]](#ast-parser)
- [Additional Infomation](#additional-information)

## Prototype

This folder contains the source file of elementary implementation of postfix notation and variable storage. You can compile it by `clang interpreter.c -o felys` and then execute it by `./felys workplace.ely`. You may find a demo in [prototype/workplace.ely](prototype/workplace.ely).

### Operation

- arithmatic: `+` `-` `*` `/`
- brackets: `(` `)`
- decimal: `3.14`

### Syntax

- case sensitive but not space sensitive
- use `=` to assign the value to the variable
- expression without assignment will be print out

## Current Version

Run `make` To compile (using clang) the program and create a temperary folder for `.o` files. You can find this script in my other repo: [Code-Collection](https://github.com/Jhanny-Kin/Code-Collection/blob/main/Make/makefile), modify the top four variables to customize the script. You can execute it by `./felys workplace.ely` or `./felys workplace.ely debug` for debugging output. You may find a heaviside function demo in [felys/workplace.ely](felys/workplace.ely). Here is the [disign explanation(CHN)](https://www.bilibili.com/read/readlist/rl738985).

### Operation

- arithmatic: `+` `-` `*` `/`
- brackets: `(` `)`
- decimal: `3.14`
- negation: `-3`
- comparison: `>` `<` `=`

### Syntax

- case sensitive but not space sensitive
- use `<-` to assign the value to the variable
- Similar to python syntax: strict indetation, no semicolons/brace
- Support keywords: `while` `if` `elif` `goto` `else` `exit` `show`

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

If all the features all implemented, the new interpreter will be dynamic typing and can calculate almost infinitly large numbers. However, as a first-year university student, I really lack in-depth knowledge related to programming language and compiler, so I think it would be a good idea to stop here. I will definitly come back to finish this program in the future, but for now, I have to move on with my school work and co-op. The followings are some **key designs**. Since they are complicated, I won't explain them here.

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

## AST Parser

Surprise, it's written in Rust (this is merged from another repo that is already removed). The Felys-Interpreter is very likely to move to Rust because it's way too time consuming to build wheels in C. Rust does not have GC and can reach same performance as C++, so why not?

### Compilation

Make sure you can run `cargo` on your device. Navigate to where `Cargo.toml` locates and run `cargo build --release` in terminal. Rust production level compilation might take a few seconds, and then you should find a binary file called `parser` in `./target/release`. This is the CLI programm that you will be using.

### Execution

Like ohter CLI program, you can run `./parser -h` for instructions. The acutal usage is `./parser '<INPUT>'`, and `-d` flag can switch on debug mode for more information. Make sure you wrap the expression with single quatation marks. The program covers most of operators, except for `->` `++` `+=` `>>` `sizeof` and a few more. Some dialectal operators like `and` `or` `**` `=>` are also excluded.

### Example

This parses and converts `x=1+foo("elysia", y, 2)` into `( = x ( + 1 ( foo "elysia" y 2 ) ) )`, and prints out all info.

```
./parser 'x=1+foo("elysia", y, 2)' -d
```

```
Debug: true
Expr: "x=1+foo(\"elysia\", y, 2)"

TokenType       Start   End     Value
Identifier      0       1       x
BinaryOper      1       2       =
Numerical       2       3       1
BinaryOper      3       4       +
FuncCall        4       7       foo
OpenParen       7       8       (
StringVar       8       16      "elysia"
ParamSplit      16      17      ,
Identifier      18      19      y
ParamSplit      19      20      ,
Numerical       21      22      2
CloseParen      22      23      )

Node {
    typing: BinaryOper,
    value: "=",
    branch: [
        Node {
            typing: Identifier,
            value: "x",
            branch: [],
        },
        Node {
            typing: BinaryOper,
            value: "+",
            branch: [
                Node {
                    typing: Numerical,
                    value: "1",
                    branch: [],
                },
                Node {
                    typing: FuncCall,
                    value: "foo",
                    branch: [
                        Node {
                            typing: StringVar,
                            value: "\"elysia\"",
                            branch: [],
                        },
                        Node {
                            typing: Identifier,
                            value: "y",
                            branch: [],
                        },
                        Node {
                            typing: Numerical,
                            value: "2",
                            branch: [],
                        },
                    ],
                },
            ],
        },
    ],
}

( = x ( + 1 ( foo "elysia" y 2 ) ) )
```

## Additional Information

The name "felys" is a combination of my two favourite game characters **Pardofelis** and **Elysia** (both from Honkai Impact 3rd).
