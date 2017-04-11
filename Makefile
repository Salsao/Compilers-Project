all: c rc

c:
	flex -i trab4.l
	bison trab4.y -v
	gcc -c hash.c pilha.c arvore.c
	gcc -o trab4 trab4.tab.c -lfl hash.o pilha.o arvore.o -lm

rc: 
	clear all
	./trab4 < input.gpt

r: 
	./trab4 < input.gpt

clean: 
	-rm -f *.o *.output lex.yy.c trab4.tab.c

latex: 	
	pdflatex trab4

cleantex:
	-rm -f trab4.aux trab4.pdf
