CC= gcc
LEX= flex
YACC= bison

FILE_lex= B113040052.l
FILE_YACC= B113040052.y

all: clean lib/libsymbol_table.a yacc lex
	${CC} B113040052.tab.o lex.o lib/libsymbol_table.a -lfl -lstdc++ -static -o yacc.elf

clean:
	rm -rf lib/build B113040052.tab.o lex.o yacc.elf lex.c
	rm -f B113040052.tab.c B113040052.tab.h B113040052.output B113040052.dot B113040052.jpg

lib/libsymbol_table.a: lib/symbol_table.c lib/symbol_table.h
	mkdir -p lib/build
	${CC} -c lib/symbol_table.c -o lib/build/symbol_table.o
	ar rcs lib/libsymbol_table.a lib/build/symbol_table.o

lex: ${LEX_RULE}
	${LEX} -o lex.c ${FILE_lex}
	${CC} -c lex.c

yacc: ${YACC_RULE}
	${YACC} -g -vd -Wnone ${FILE_YACC}
	${CC} -c B113040052.tab.c

dot: yacc
	dot -T jpg B113040052.dot -o B113040052.jpg

test: all
	for i in $$(seq 1 6); do ./yacc.elf < test/test$$i.java; echo; done
