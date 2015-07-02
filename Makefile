shell: shell.o lex.yy.o
	cc -o shell lex.yy.o shell.o -lfl

shell.o: shell.c
	cc -c shell.c

lex.yy.o: lex.yy.c
	cc -c lex.yy.c

lex.yy.c: lex.c
	flex lex.c

clean:
	rm shell *.o
