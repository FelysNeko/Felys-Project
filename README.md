# Felys-Interpreter

Simple Math Interpreter - application of postfix notatioin (reverse polish notation)

## Compilation and Run

Run `make` To compile (using clang) the program and create a temperary folder for `.o` files. You can find this script in my other repo: [Code-Collection](https://github.com/Jhanny-Kin/Code-Collection/blob/main/Make/makefile), modify the top four variables to customize the script. Then you can use `make clean` To clean up the temperary folder with `.o` file in it and `felys` the binary code.


To execute the program. Note there is a heaviside function demo in [workplace.ely](v1.1/workplace.ely)
```shell
./felys workplace.ely
```

If you want to see the stucture behind, you can execute `./felys workplace.ely debug`


## Operation
1. arithmatic: `+` `-` `*` `/`
2. brackets: `(` `)`
3. decimal: `3.14`
4. negation: `-3`
5. comparison: `>` `<` `=`

Example: `1+(-3/4.5-2) > (0.5*(1+3/2)-1)/2`

## Syntax 
1. case sensitive but not space sensitive
2. use `<-` to assign the value to a variable (left side)
3. Similar to python syntax: strict indetation, no semicolons/brace
4. Support keywords: `while` `if` `elif` `goto` `else` `exit` `show`


## Additional Information

* This is my first major C project, and the difficulty is way way beyond the scope for a self-taught beginner. After I finished the first term in University, I realizad how bad some parts of the code are formatted or designed, though I'm still quite proud of Felys anyway.
* The name "Felys" is the combination of my favourite two game characters **Elysia** and **Pardofelis** (from Honkai Impact 3rd).
* Here is the [Deisgn Explanation(CHN)](https://www.bilibili.com/read/readlist/rl738985)
