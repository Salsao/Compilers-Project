#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

typedef struct pilha Pilha;
typedef struct item Item;
typedef struct variavel Variavel;
typedef struct funcao Funcao;
typedef struct lista Lista;

typedef struct arvore Arvore;
typedef struct arvore_pilha Arvore_pilha;

Lista* inicializa (void);
Lista** inicializa_hash (void);
int vazia (Lista* l);
Lista* busca (Lista** l, char c[], int escopo);
int verifica_tipo(Lista** h, char expressao[], int escopo);
int verifica_tipo_parametros_funcao(Lista** h, char funcao[],Lista* l);
int set_usada (Lista *l);
void set_valor (Lista *l, float valor);
void set_valor_string (Lista *l, char *str);
void libera (Lista* l);
void edita_para_matriz(Lista* l, int m, int n);
Lista* insere_variavel_lista(Lista* l, char nome[], int usada);
Lista* insere_lista_lista(Lista* l, Lista* p);
Lista* insere_variavel_lista1(Lista* l, char nome[], int tipo, int escopo, int usada);
Lista** insere_variavel_hash(Lista** h, Lista* l, int tipo,int escopo);
Lista** insere_variavel_hash_valor(Lista** h, Lista* l, float valor);
Lista** insere_variavel_hash_string(Lista** h, Lista* l, char* str);
Lista** insere_variavel_hash_vetor(Lista** h, Lista* l, float m);
Lista** insere_variavel_hash_matriz(Lista** h, Lista* l, float m, float n);
Lista** insere_variavel (Lista** l, char nome[], int tipo, int usada, int escopo, int m, int n);
Lista* insere_funcao_lista(Lista* l, char nome[]);
Lista** insere_funcao_hash(Lista** h, Lista* l, int retorno, int aridade);
Lista** insere_parametro_funcao(Lista** h, char nome[], int tipo_parametros[]);
Lista** insere_funcao (Lista** l, char nome[], int retorno, int aridade);
void imprime_hash(Lista** l);
void imprime (Lista* l);
void verifica_variavel_usada(Lista** l);
void verifica (Lista* l);
int get_tipo(Lista* l);
float get_valor_float(Lista* l);
float get_valor_int(Lista* l);
char get_valor_char(Lista* l);
char* get_valor_string(Lista* l);
int get_escopo(Lista* l);
int get_usada(Lista* l);
char* get_nome(Lista* l);
int get_m(Lista* l);
int get_n(Lista* l);
int get_aridade(Lista* l);
int get_retorno(Lista* l);
Arvore* insere_lista_arvore(Lista* l);

#endif /* HASH_H */
