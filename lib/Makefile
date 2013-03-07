CC=g++
CFLAGS=-c
LDFLAGS=-lfl -ly

all: bnK-lang

bnK-lang: builtins.o node.o object.o number.o string.o udf.o interpreter.o context.o lexer.o parser.o
    $(CC) $(LDFLAGS) builtins.o node.o object.o number.o string.o udf.o interpreter.o context.o lexer.o parser.o -o $@

builtins.o: builtins.cpp
    $(CC) $(CFLAGS) ./builtins/builtins.cpp -o $@

node.o: node.cpp
    $(CC) $(CFLAGS) ./nodes/node.cpp -o $@

number.o: number.cpp
    $(CC) $(CFLAGS) ./types/number.cpp -o $@

string.o: string.cpp
    $(CC) $(CFLAGS) ./types/string.cpp -o $@

udf.o: udf.cpp
    $(CC) $(CFLAGS) ./types/udf.cpp -o $@

interpreter.o: interpreter.cpp
    $(CC) $(CFLAGS) ./interpreter.cpp -o $@

context.o: context.cpp
    $(CC) $(CFLAGS) ./context.cpp -o $@

lexer.o: lex.yy.c
    $(CC) $(CFLAGS) ./lex.yy.c -o $@

parser.o: y.tab.c
    $(CC) $(CFLAGS) ./y.tab.c -o $@

clear:
        rm *.o
