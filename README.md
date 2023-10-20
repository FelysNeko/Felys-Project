# Felys (v1.0: Official Release)

Simple Math Interpreter - application of postfix notatioin (reverse polish notation)

To compile the program (please use clang instead of gcc since the latter cause unexpected issues when compiling on Linux)
```shell
clang main.c -o felys
```

To execute the program, note there is a heaviside functions demo in "workplace.ely"
```shell
./felys workplace.ely
```

To see the debugging output
```shell
./felys workplace.ely debug
```


The name "Felys" is the combination of my favourite two game characters **Elysia** and **Pardofelis** (from Honkai Impact 3rd).

Operation supported:
1. basis: + - * /
2. brackets: ( )
3. decimals: [a].[b]
4. negation: -x
5. comparison: > < =

Syntax (case sensitive but not space sensitive):
1. use '<-' to assign a value to the variable (left side)
2. Similar to python syntax: strict indetation, no semicolons/brace
3. Support keywords: while, if, elif, goto, else, exit, show

Document(Chinese): https://www.bilibili.com/read/readlist/rl738985
