CC=g++
CFLAGS=-c
LDFLAGS=-lfl -ly

all: bnK-lang

bnK-lang: builtins.o node.o object.o number.o string.o udf.o interpreter.o context.o binaryop.o parser.o lexer.o
	$(CC) -o $@ builtins.o node.o object.o number.o string.o udf.o binaryop.o interpreter.o context.o lexer.o parser.o -lfl -ly
	rm *.o

builtins.o: 
	$(CC) $(CFLAGS) ./builtins/builtins.cpp -o $@

node.o: 
	$(CC) $(CFLAGS) ./nodes/node.cpp -o $@

object.o:
	$(CC) $(CFLAGS) ./types/object.cpp -o $@

number.o: 
	$(CC) $(CFLAGS) ./types/number.cpp -o $@

string.o: 
	$(CC) $(CFLAGS) ./types/string.cpp -o $@

udf.o: 
	$(CC) $(CFLAGS) ./types/udf.cpp -o $@

binaryop.o:
	$(CC) $(CFLAGS) ./binaryop.cpp -o $@

interpreter.o: 
	$(CC) $(CFLAGS) ./interpreter.cpp -o $@

context.o: 
	$(CC) $(CFLAGS) ./context.cpp -o $@

lexer.o: 
	lex lexer.l
	$(CC) $(CFLAGS) ./lex.yy.c -o $@

parser.o:
	yacc -dv parser.yacc
	$(CC) $(CFLAGS) ./y.tab.c -o $@

clear:
	rm *.o
