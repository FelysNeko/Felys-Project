# Felys(v0.4)

Simple Math interpreter - application of postfix notatioin (reverse polish notation)

Some sample codes that can be understood by interpreter are in "workplace.ely". You can use command "./felys workplace.ely" to see the ouput, make sure you add execution permission to "felys". The syntax check is pretty weak, but the interpreter does list all the interlayers for you to look at.

The name "Felys" is the combination of my favourite two game characters **Elysia** and **Pardofelis** (from Honkai Impact 3rd).


Operation supported:
1. basis: + - * /
2. brackets: ()
3. decimals: [int].[dec]
4. negation: -x
5. comparison: > < =

Syntax (case sensitive but not space sensitive):
1. use '<-' to assign a value to the left side
2. Similar to pythons, having strict indetation
3. Support: while, if, elif, goto, else, exit
4. See code examples in "workplace.ely"


I will write a detailed document later to explain the core concepts of my design, so you will have a better understanding of my work.
