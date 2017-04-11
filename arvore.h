#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "pilha.h"

typedef struct pilha Pilha;
typedef struct item Item;
typedef struct variavel Variavel;
typedef struct funcao Funcao;
typedef struct lista Lista;

typedef struct arvore Arvore;
typedef struct arvore_pilha Arvore_pilha;

Arvore* inicializa_arvore (void);
void set_tipo_arvore(Arvore *a,char tipo[]);
void set_valor_arvore(Arvore *a,char comando[]);
void set_f1(Arvore *a,Arvore *f1);
void set_f2(Arvore *a,Arvore *f2);
void set_f3(Arvore *a,Arvore *f3);
void set_f4(Arvore *a,Arvore *f4);
void set_prox(Arvore *a,Arvore *prox);
char* get_tipo_arvore(Arvore *a);
char* get_valor_arvore(Arvore *a);
Arvore* get_f1(Arvore *a);
Arvore* get_f2(Arvore *a);
Arvore* get_f3(Arvore *a);
Arvore* get_f4(Arvore *a);
Arvore* get_prox(Arvore *a);
Arvore* get_final(Arvore *a);

Arvore *cria_arvore(char tipo[], char valor[]);
Arvore * insere_arvore(Arvore *a, char tipo[], char valor[]);
Arvore *insere_arvore_final(Arvore *final, Arvore *a);
Arvore *insere_arvore_arvore(Arvore *arvore, Arvore *a);
void arvore_imprime(Arvore* a);
void arvore_imprime_final(Arvore *a);

float executa_expressao(Arvore *a, Lista **tab_variaveis);
void executa_imprima(Arvore *a, Lista **tab_variaveis);
void executa_imprima_ln(Arvore *a, Lista **tab_variaveis);
void executa_leia(Arvore *a,Lista **tab_variaveis);
Lista** executa_arvore(Arvore *a, Lista **tab_variaveis);
void executa_arvore_final(Arvore *arvore_final, Lista **tab_variaveis);
int executa_maximo(Arvore *a, Lista **tab);
int executa_minimo(Arvore *a, Lista **tab);
int executa_media(Arvore *a, Lista **tab);

Lista** executa_atrib(Arvore* a, Lista** tab_var);
Lista** executa_atribuicao (Arvore *a, Lista **tab_variaveis);
Arvore_pilha* inicializa_arvpilha();
Arvore* arvpilha_get_arvore(Arvore_pilha* p);
Arvore_pilha* insere_arvpilha(Arvore_pilha *pilha, Arvore *a);
Arvore_pilha* remove_arvpilha(Arvore_pilha *pilha);
Arvore* topo_arvpilha (Arvore_pilha *pilha);
Arvore* remove_final_arvpilha (Arvore_pilha *pilha);
int tamanho_arvpilha(Arvore_pilha *pilha);
Arvore* monta_arvore_atribuicao(Arvore_pilha *pilha);
void arvpilha_imprime(Arvore_pilha *a);
void executa_se(Arvore* arv, Lista** tab_var);
Arvore* arvore_insereOp(char op, Arvore* v1, Arvore* v2);
Arvore* arvore_monta_exp(Pilha* p);
int avaliaExpressaoInt(Arvore *a, Lista** tabela_hash_var, int ESCOPO_VAR);
float avaliaExpressaoFloat(Arvore *a, Lista** tabela_hash_var, int ESCOPO_VAR);
void leia();

#endif /* ARVORE_H */
