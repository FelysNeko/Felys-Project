# Felys (v1.0: Official Release)

Simple Math interpreter - application of postfix notatioin (reverse polish notation)

**Some sample codes that interpreter understands are in "workplace.ely".** You can compile the program by command "gcc main.c -o felys" (if you are using Linux/Mac), and then type command "./felys workplace.ely" to see the ouput. If you want to see all the interlayers of the interpreter, you can use command "./felys workplace.ely debug" to get the details. Note that show command will not function in this mode.

The name "Felys" is the combination of my favourite two game characters **Elysia** and **Pardofelis** (from Honkai Impact 3rd).

Operation supported:
1. basis: + - * /
2. brackets: ( )
3. decimals: [int].[dec]
4. negation: -x
5. comparison: > < =

Syntax (case sensitive but not space sensitive):
1. use '<-' to assign a value to the variable (left side)
2. Similar to python syntax: strict indetation, no semicolons/brace
3. Support keywords: while, if, elif, goto, else, exit, show

Document(CN): https://www.bilibili.com/read/readlist/rl738985

# Future Plan
After I finished this project, I taught myself 8086 assembly a bit which inspired me a new idea: building a simulator for assembly language. There are similarities between Felys and the new project I'm thinking of. However, before I really work on this new project, I need to spend more time learning assembly and C (maybe C++ since it will be in my first year uni course). Also, I'm moving to another country for univeristy, meaning that the following term will be extremely busy, so optimistically speaking, the new project won't start till Christmas.

# Note
Parsing might not function sometimes, so I will try to fix it if I have time. However, I am currently redesigning Felys, so chances are I come up with a new version and not fiox the old bug.
