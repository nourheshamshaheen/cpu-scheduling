
#Use GNU compiler
cc = gcc -g
CC = g++ -g

all: lab4

lex.yy.o: lab4.l 
	lex lab4.l
	$(cc) -c lex.yy.c

y.tab.o: lab4.y
	yacc -d lab4.y
	$(CC) -c y.tab.c

command.o: command.cc
	$(CC) -c command.cc

lab4: y.tab.o lex.yy.o command.o
	$(CC) -o lab4 lex.yy.o y.tab.o command.o -ll

clean:
	rm -f lex.yy.c y.tab.c  y.tab.h lab4 *.o file.log

