# Felys

Calulation interpreter, also an application of postfix notatioin (reverse polish notation)

Some sample codes that can be understood by interpreter are in "workplace.ely". You can use command "./felys workplace.ely" to see the ouput, make sure you add execution permission to "felys". The interpreter does not have syntax check, so it might easily crash if there is any error in the script.

I am still a C beginer, and this interpreter is for a fun practice. Please don't judge me too critically. The name "Felys" is the combination of my favourite two characters **Elysia** and **Pardofelis**


Operation suppoeted:
1. basis: + - * /
2. brackets: ()
3. decimals: x.d
4. negation: -x

Syntax (case sensitive but not space sensitive):
1. use '=' to assign a value to the left side
2. directly type the calculation to output the result (similar to jupyter notebook)
