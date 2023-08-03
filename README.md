# Felys (v1.0: Official Release)

Simple Math interpreter - application of postfix notatioin (reverse polish notation)

Some sample codes that interpreter understands are in "workplace.ely". You can compile the program by command "gcc main.c -o felys" (if you are using Linux/Mac), and then type command "./felys workplace.ely" to see the ouput. If you want to see all the interlayers of the interpreter, you can use command "./felys workplace.ely debug" to get the details. Note that show command will not function in this mode.

The name "Felys" is the combination of my favourite two game characters **Elysia** and **Pardofelis** (from Honkai Impact 3rd).

Operation supported:
1. basis: + - * /
2. brackets: ( )
3. decimals: [int].[dec]
4. negation: -x
5. comparison: > < =

Syntax (case sensitive but not space sensitive):
1. use '<-' to assign a value to the left side
2. Similar to python, meaning strict indetation
3. Support: while, if, elif, goto, else, exit, show

Document(CN): https://www.bilibili.com/read/readlist/rl738985
