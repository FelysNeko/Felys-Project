cc=clang

felys: main.o function.o parse.o postfix.o variable.o stack.o
	$(cc) main.o function.o parse.o postfix.o variable.o stack.o -o felys

main.o: main.c
	$(cc) -c main.c

function.o: function.c
	$(cc) -c function.c

parse.o: parse.c
	$(cc) -c parse.c

postfix.o: postfix.c
	$(cc) -c postfix.c

stack.o: stack.c
	$(cc) -c stack.c

variable.o: variable.c
	$(cc) -c variable.c

clean:
	rm *.o
