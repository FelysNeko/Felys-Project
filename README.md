# Felys (v1.1: Official Release)

Simple Math Interpreter - application of postfix notatioin (reverse polish notation)

## Compilation and Run

To compile (using clang) the program and create a temperary folder for `.o` files. You can find this script in my other repo: [Code-Collection](https://github.com/Jhanny-Kin/Code-Collection/blob/main/Make/makefile), modify the top three variables to customize the script.
```shell
make
```

To clean up all the temperary folder with `.o` file in it and `felys` the binary code
```shell
make clean
```

Execute the program, note there is a heaviside function demo in [workplace.ely](v1.1/workplace.ely)
```shell
./felys workplace.ely
```

To see the debugging output
```shell
./felys workplace.ely debug
```


## Operation
1. basis: `+` `-` `*` `/`
2. brackets: `(` `)`
3. decimals: `3.14`
4. negation: `-3`
5. comparison: `>` `<` `=`

Example:
```
1+(-3/4.5-2) > (0.5*(1+3/2)-1)/2
```

## Syntax 
1. case sensitive but not space sensitive
2. use `<-` to assign a value to the variable (left side)
3. Similar to python syntax: strict indetation, no semicolons/brace
4. Support keywords: `while`, `if`, `elif`, `goto`, `else`, `exit`, `show`


## Additional Information

The name "Felys" is the combination of my favourite two game characters **Elysia** and **Pardofelis** (from Honkai Impact 3rd).

Deisgn explanation(Chinese): [LINK](https://www.bilibili.com/read/readlist/rl738985)
