#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"


struct pilha {
	Item *topo;
};

struct item {
	int tipo;
	float real;
	// esse char eh pra armazenar os elementos da expressao infixada pra transformar pra posfixada
	char doge; // '^' = pot, '*' = mult, '/' = div, '+' = soma, '-' = subtracao
	char *variavel;
	Arvore* deku;
	struct item *prox;
};

int pilha_tamanho(Pilha *pilha) {
	Item *pont;
	int tam = 0;

	if (pilha_vazia(pilha)) {
		return 0;
	}

	for (pont = pilha->topo; pont; pont = pont->prox) {
		tam++;
	}

	return tam;
}

void pilha_imprime(Pilha *pilha) {
	Item *pont;
	

	printf("Tamanho: %d\n", pilha_tamanho(pilha));	
	printf(" topo| ");
	for (pont = pilha->topo; pont; pont = pont->prox) {
		if (pont->doge == 'n'){
			printf("%d | ", pont->tipo);
		}
		else if(pont->doge == 'N'){
			printf("%f | ", pont->real);
		}
		else {
			printf("%c | ", pont->doge);
		}
	}
	printf("\n");
	return;
}

int get_tipo_pilha(Pilha *p){
	return p->topo->tipo;
}

float get_real(Pilha *p){
	return p->topo->real;
}

char get_doge(Pilha *p){
	return p->topo->doge;
}

char* get_var(Pilha *p){
	return p->topo->variavel;
}

char get_doge2(Item *p){
	return p->doge;
}

Item* get_topo(Pilha *p){
	if (p->topo != NULL){
		return p->topo;
	}
	else{
		return NULL;
	}
}

Arvore* get_arvore(Pilha *p){
	return p->topo->deku;
}

int prioridade(char op){
	switch(op){
		case '(': return 10;
			break;
		case '^': return 3;
			break;
		case '*': return 2;
			break;
		case '/': return 2;
			break;
		case '%': return 2;
			break;
		case '+': return 1;
			break;
		case '-': return 1;
			break;
		case '&': return 2;
			break;
		case '|': return 2;
			break;
		case '!': return 3;
			break;
		default: printf(" Deu ruim na expressao! Pegou %c\n", op);
	}
}


Pilha *pilha_constroi() {
	Pilha *pilha;
	pilha = (Pilha *)malloc(sizeof(Pilha));
	pilha->topo = NULL;
	return pilha;
}

int pilha_vazia(Pilha *pilha) {
	if(!pilha->topo) {
		return 1;
	}
	return 0;
}



void pilha_insere(Pilha *pilha, int inteiro) {
	Item *novo;
	novo = (Item *)malloc(sizeof(Item));
	novo->tipo = inteiro;
	novo->doge = 'n';
	novo->prox = pilha->topo;
	pilha->topo = novo;
}

void pilha_insert(Pilha *pilha, float re) {
	Item *novo;
	novo = (Item *)malloc(sizeof(Item));
	novo->real = re;
	novo->doge = 'N';
	novo->prox = pilha->topo;
	pilha->topo = novo;
}

void pilha_putIn(Pilha *pilha, char wow) {
	Item *novo;
	novo = (Item *)malloc(sizeof(Item));
	novo->doge = wow; 
	novo->prox = pilha->topo;
	pilha->topo = novo;
}

void pilha_putVar(Pilha *pilha, char va[]) {
	Item *novo;
	novo = (Item *)malloc(sizeof(Item));
	novo->variavel = (char*) malloc ((strlen(va)+1)*sizeof(char));
	strcpy(novo->variavel,va);
	novo->doge = 'v';
	novo->prox = pilha->topo;
	pilha->topo = novo;
}

void pilha_plantar(Pilha *pilha, Arvore* a){
	Item *novo;
	novo = (Item *)malloc(sizeof(Item));
	novo->doge = 'm';
	novo->deku = a;
	novo->prox = pilha->topo;
	pilha->topo = novo;
	
}

int pilha_remove(Pilha *pilha) {
	Item *pont;
	if(pilha_vazia(pilha)) {
		return -1;
	}
	pont = pilha->topo;
	pilha->topo = pilha->topo->prox;
	return pont->tipo;
}

float pilha_tira(Pilha *pilha) {
	Item *pont;
	if(pilha_vazia(pilha)) {
		return -1;
	}
	pont = pilha->topo;
	pilha->topo = pilha->topo->prox;
	return pont->real;
}

char pilha_putOut(Pilha *pilha) {
	Item *pont;
	if(pilha_vazia(pilha)) {
		return -1;
	}
	pont = pilha->topo;
	pilha->topo = pilha->topo->prox;
	return pont->doge;
}

char* pilha_outVar(Pilha *pilha) {
	Item *pont;
	if(pilha_vazia(pilha)) {
		return NULL;
	}
	pont = pilha->topo;
	pilha->topo = pilha->topo->prox;
	return pont->variavel;
}

Arvore* pilha_desmatar(Pilha *pilha){
	Item *pont;
	if(pilha_vazia(pilha)) {
		return NULL;
	}
	pont = pilha->topo;
	pilha->topo = pilha->topo->prox;
	return pont->deku;
}

void pilha_destroi(Pilha *pilha) {
	int i;
	Pilha* aux = pilha;
	while(aux->topo != NULL)
	{
		i = pilha_remove(pilha);
	}
	free(aux);
}

Pilha* pilha_inverte(Pilha *pilha){
	Pilha *invertida;
	invertida = (Pilha *)malloc(sizeof(Pilha));
	invertida->topo = NULL;
	int num;

	while(!pilha_vazia(pilha)){
		if (pilha->topo->doge == 'n'){
			num = pilha_remove(pilha);
			pilha_insere(invertida, num);
		}
		else if(pilha->topo->doge == 'N'){
			pilha_insert(invertida, pilha_tira(pilha));
		}
		else if (pilha->topo->doge == 'v'){
			pilha_putVar(invertida, pilha_outVar(pilha));
		}
		else{
			pilha_putIn(invertida, pilha->topo->doge);
			pilha_putOut(pilha);
		}	
	}
	return invertida;
}

Pilha *pilha_posfixar(Pilha *pilha_exp) {
	Pilha *pilha_saida;
	pilha_saida = (Pilha *)malloc(sizeof(Pilha));
	pilha_saida->topo = NULL;

	Pilha *pilha_op;
	pilha_op = (Pilha *)malloc(sizeof(Pilha));
	pilha_op->topo = NULL;

	Item *aux;
	Item *pont;
	int doge;
	for (aux = pilha_exp->topo; aux; aux = aux->prox){
		if(pilha_exp->topo->doge == 'n'){//Eh numero
			pilha_insere(pilha_saida, pilha_remove(pilha_exp));
		}
		else if(pilha_exp->topo->doge == 'N'){// Eh real
			pilha_insert(pilha_saida, pilha_tira(pilha_exp));
		}
		else if(pilha_exp->topo->doge == 'v'){// Eh variavel
			pilha_putVar(pilha_saida, pilha_outVar(pilha_exp));
		}
		else{
			if(pilha_vazia(pilha_op)){
				pilha_putIn(pilha_op, pilha_putOut(pilha_exp));
			}
			else{
				if(pilha_exp->topo->doge == '('){
					pilha_putIn(pilha_op, pilha_putOut(pilha_exp));
				}
				//encountrou ), temos que pegar tudo que esta na pilha_op até o ( e jogar para saida
				else if(pilha_exp->topo->doge == ')'){
					while(pilha_op->topo->doge != '('){
						pilha_putIn(pilha_saida, pilha_putOut(pilha_op));
					}
					pilha_putOut(pilha_exp);
					pilha_putOut(pilha_op);
				}
				else if(prioridade(pilha_exp->topo->doge) > prioridade(pilha_op->topo->doge)){
					pilha_putIn(pilha_op, pilha_putOut(pilha_exp));
				}
				else if (prioridade(pilha_exp->topo->doge) == prioridade(pilha_op->topo->doge)){
					pilha_putIn(pilha_saida, pilha_putOut(pilha_op));
					pilha_putIn(pilha_op, pilha_putOut(pilha_exp));
				}
				else{
					doge = 1;
					while(doge){
						if (pilha_vazia(pilha_op)){
							doge = 0;
							pilha_putIn(pilha_op, pilha_putOut(pilha_exp));
						}
						else if(pilha_op->topo->doge == '('){
							pilha_putIn(pilha_op, pilha_putOut(pilha_exp));
							doge = 0;
						}
						else if (prioridade(pilha_exp->topo->doge) <= prioridade(pilha_op->topo->doge)){
							pilha_putIn(pilha_saida, pilha_putOut(pilha_op));
						}
						else{
							pilha_putIn(pilha_op, pilha_putOut(pilha_exp));	
						}
					}
				}
			}
		}
	}
	while(!pilha_vazia(pilha_op)){
		pilha_putIn(pilha_saida, pilha_putOut(pilha_op));
	}
	pilha_saida = pilha_inverte(pilha_saida);
	return pilha_saida;
}

int pilha_verifica_compatibilidade(Pilha *pilha) {
	int primeiro, segundo;

	if(pilha_tamanho(pilha) > 1) {
		primeiro = pilha_remove(pilha);
		segundo = pilha_remove(pilha);

		/* // coersão, operaçoes envolvendo int e real retornam real
		if(primeiro == 0 && segundo == 3 || primeiro == 3 && segundo == 0) {
			pilha_insere(pilha, 3);
		}
		else*/
		if(primeiro != segundo) {
			return 0;
		}
		else if (primeiro == segundo) {
			pilha_insere(pilha, primeiro);	
		}
	}
	return 1;
}
/*
Arvore* insere_variavel_arvore(Arvore* h, Lista* l, char* valor){
	Lista* p;
	Variavel* v;
	Arvore* a, aux, aux2;
	a = cria
	for(p=l;p!=NULL;p=p->prox){
		v = (Variavel*)p->info;
		aux = cria_arvore("variavel", v->nome);
		while(aux->prox != NULL){
			aux = aux->prox;
		}
		set_prox(a, aux);
		//set_valor(busca(h, v->nome, v->escopo), valor);
	}
	set_f1(h, a);
	return h;
}
*/