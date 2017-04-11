#ifndef PILHA_H
#define PILHA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

typedef struct arvore Arvore;
typedef struct arvore_pilha Arvore_pilha;
typedef struct variavel Variavel;
typedef struct funcao Funcao;
typedef struct lista Lista;

typedef struct pilha Pilha;
typedef struct item Item;

int pilha_tamanho(Pilha *pilha);
void pilha_imprime(Pilha *pilha);
int get_tipo_pilha(Pilha *p);
float get_real(Pilha *p);
char get_doge(Pilha *p);
char* get_var(Pilha *p);
char get_doge2(Item *p);
Item* get_topo(Pilha *p);
Arvore* get_arvore(Pilha *p);
int prioridade(char op);
Pilha *pilha_constroi();
int pilha_vazia(Pilha *pilha);
void pilha_insere(Pilha *pilha, int inteiro);
void pilha_insert(Pilha *pilha, float re);
void pilha_putIn(Pilha *pilha, char wow);
void pilha_putVar(Pilha *pilha, char va[]);
void pilha_plantar(Pilha *pilha, Arvore* a);
int pilha_remove(Pilha *pilha);
float pilha_tira(Pilha *pilha);
char pilha_putOut(Pilha *pilha);
char* pilha_outVar(Pilha *pilha);
Arvore* pilha_desmatar(Pilha *pilha);
void pilha_destroi(Pilha *pilha);
Pilha* pilha_inverte(Pilha *pilha);
Pilha *pilha_posfixar(Pilha *pilha);
int pilha_verifica_compatibilidade(Pilha *pilha);

#endif /* PILHA_H */
