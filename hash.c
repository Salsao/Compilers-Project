#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

#define TAM 97

extern int nlinhas;


struct variavel{
	char *nome;
	void *valor;
	int tipo; //inteiro=0, real = 1, logico = 2, caracter=3, literal=4
	int escopo; //global=0, local>0 
	int usada;
	int matriz[1]; // 1 1; m x 1 ou 1 x m; m x n
};

struct funcao{
	char *nome;
	int  retorno; // inteiro=0, caracter=1, string=2, real=3, booleano =4, void = -1
	int  aridade; 
	int  tipo_parametros[10];//cada funcao pode ter no maximo 10 parametros
};

//tipo pode ser variavel=0 funcao=1
struct lista{
	int tipo;
	void *info;
	struct lista *prox;
};


Lista* inicializa (void){
	return NULL;
}

Lista** inicializa_hash (){
	int i;
	Lista **v;
	v = (Lista**) malloc(TAM*sizeof(Lista*));
	for(i=0; i<TAM;i++){
		v[i] = inicializa();	
	}
	return v;
}



int vazia (Lista* l){
	if(l==NULL)
		return 1;
	else
		return 0;

}
//Busca uma variavel ou fum funcao na tabela hash, caso nao encontre retorna NULL, foi necessario inserir escopo para a variavel, se for buscar funcao pode colocar quaquer coisa em escopo que nao tem problema, pois so sera usado para variaveis
Lista* busca (Lista** l, char nome[], int escopo){
	Lista* p;
	Variavel *v;
	Funcao *f;
	char c;
	int pos,i;	
	pos=0;
	c=nome[0];
	pos =pos+(int)c;
	i=1;
	while(c!='\0'){
			
		c=nome[i];
		pos=pos+(int)c;
		i++;
	}
	
	pos = pos%TAM;
	for(p=l[pos]; p!=NULL; p=p->prox){
		if(p->tipo ==0){
			v = (Variavel*)p->info;
			if(strcmp(v->nome,nome)==0 && v->escopo==escopo){
				return p;			
			}
		}
		if(p->tipo ==1){
			f = (Funcao*)p->info;
			if(strcmp(f->nome,nome)==0){
				return p;			
			}		
		}
	}
	return NULL;	
}
//dada uma hash e uma expressao verifica se o tipo das variaveis da expressao sao compativeis
int verifica_tipo(Lista** h, char expressao[], int escopo){
	char var[40];
	int i=1,j=0,tipo=-1;
	Lista* l;
	Variavel* v;
	while(expressao[i]!='\0'){
		//separa cada variavel na expressao
		while(expressao[i]!='-' && expressao[i]!='\0'){
			var[j] = expressao[i];
			i++;
			j++;
		}
		i++;
		var[j] = '\0';
		j=0;
		//busca a variavel na tabela de variaveis
		l = busca(h,var, escopo);
		if(l!=NULL){
			if(l->tipo == 0){
				v = (Variavel*) l->info;
				if(tipo == -1){
					tipo = v->tipo;
				}
				else{
					//se tiver algum tipo diferente retorna 0
					if (tipo != v->tipo)
						return 0;
				}
			}else if(l->tipo == 1){
			}
				
			
		}
	}
	//se todos os tipos forem iguais retorna 1
	return 1;
}
int verifica_tipo_parametros_funcao(Lista** h, char funcao[],Lista* l){
	Lista *lis, *aux;
	Funcao *f;
	Variavel *v;
	int i=0;
	
	lis = busca(h,funcao,0);
	f = (Funcao*)lis->info;
	
	for (aux=l; aux!=NULL; aux=aux->prox){
		v = (Variavel *)aux->info;
		if(f->tipo_parametros[i] != v->tipo)
			return 0; 
		i++;
	}
	return 1;
}

int set_usada (Lista *l){
	Variavel *v;
	v= (Variavel*)l->info;
	v->usada =1; 
}

void set_valor (Lista *l, float valor){
	Variavel *v;
	v= (Variavel*)l->info;
	if(v->tipo == 0){
		*(int*)v->valor = (int)valor;
	}
	else if(v->tipo == 1){
		*(float*)v->valor = valor; 
	}
}

void set_valor_string (Lista *l, char *str){
	Variavel *v;
	v = (Variavel*)l->info;
	v->valor = (char*)malloc(strlen(str) * sizeof(char));
	strcpy(v->valor, str);
}

void libera (Lista* l){
	Lista* p=l;
	while (p!=NULL){
		Lista* t = p->prox;
		free(p->info);
		free (p);
		p=t;	
	}
}

void edita_para_matriz(Lista* l, int m, int n){
	Lista* aux;
	Variavel* v = (Variavel*) malloc (sizeof(Variavel));
	for (aux = l; aux != NULL; aux = aux->prox){
		v = (Variavel*)aux->info;
		v->matriz[0] = m; 
		v->matriz[1] = n; 
	}
	
}


//insere a variavel em uma lista
Lista* insere_variavel_lista(Lista* l, char nome[], int usada){
	Lista* novo = (Lista*) malloc(sizeof(Lista));
	Variavel* var = (Variavel*) malloc (sizeof(Variavel));
	var->nome = (char*) malloc ((strlen(nome)+1)*sizeof(char));
	strcpy(var->nome,nome);
	var->valor = NULL;
	var->tipo = -1;
	var->usada = usada;
	var->escopo = -1;
	var->matriz[0] = 1;
	var->matriz[1] = 1;
	novo->info = var;
	novo->tipo = 0;
	novo->prox = l;
	l = novo;
	return l;
}

// insere p em l
Lista* insere_lista_lista(Lista* l, Lista* p){ 
	Lista* aux = l;
	if (l == NULL){
		l = p;
	}
	else{ 
			while (aux->prox != NULL){
			aux = aux->prox;
		}
		aux->prox = p;
	}
	return l;
}


Lista* insere_variavel_lista1(Lista* l, char nome[], int tipo, int escopo, int usada){
	Lista* aux;
	Lista* novo = (Lista*) malloc(sizeof(Lista));
	Variavel* var = (Variavel*) malloc (sizeof(Variavel));
	var->nome = (char*) malloc ((strlen(nome)+1)*sizeof(char));
	strcpy(var->nome,nome);
	var->valor = NULL;
	var->tipo = tipo;
	var->usada = usada;
	var->escopo = escopo;
	novo->info = var;
	novo->tipo = 0;
	novo->prox = NULL;
	aux = l;
	if(aux == NULL){
		l=novo;
	}else{
	
		while(aux->prox!=NULL){
			aux = aux->prox;
		}
		aux->prox = novo;
	}
	return l;
}
//insere uma lista de variaveis na tabela hash
Lista** insere_variavel_hash(Lista** h, Lista* l, int tipo, int escopo){
	Lista* p;
	Variavel* v = (Variavel*) malloc (sizeof(Variavel));
	int usada;
	char nome[100];
	int matM;
	int matN;
	
	for(p=l;p!=NULL;p=p->prox){
		
		v = (Variavel*)p->info;
		strcpy(nome,v->nome);
		usada = v->usada;
		matM = v->matriz[0];
		matN = v->matriz[1];
		if(insere_variavel(h, nome, tipo, usada,escopo, matM, matN) == NULL){
			printf("Erro semantico na linha %d. Variavel %s redeclarada. Escopo: %d \n",nlinhas, nome, escopo);
			exit(0);
			return NULL;
		}
		nome[0]='\0';
	}
	return h;
}

//insere uma lista de variaveis na tabela hash
Lista** insere_variavel_hash_valor(Lista** h, Lista* l, float valor){
	Lista* p;
	Variavel* v;
	for(p=l;p!=NULL;p=p->prox){
		v = (Variavel*)p->info;
		switch (v->tipo){
			case 0:
				set_valor(busca(h, v->nome, v->escopo), valor);
				break;
			case 1: 
				set_valor(busca(h, v->nome, v->escopo), valor);
				break;
			case 2:
				if (valor != 0){
					set_valor_string(busca(h, v->nome, v->escopo), "verdadeiro");
				}
				else{
					set_valor_string(busca(h, v->nome, v->escopo), "falso");
				}
				break;
			default:
				printf("Fufu no switch (insere var hash valor)\n");

		}
		//set_valor(busca(h, v->nome, v->escopo), valor);
	}
	return h;
}

Lista** insere_variavel_hash_string(Lista** h, Lista* l, char* str){
	Lista* p;
	Variavel* v;
	for(p=l;p!=NULL;p=p->prox){
		v = (Variavel*)p->info;
		switch (v->tipo){
			case 3:
				set_valor_string(busca(h, v->nome, v->escopo), str);
				break;
			case 4: 
				set_valor_string(busca(h, v->nome, v->escopo), str);
				break;
			default:
				printf("Fufu no switch (insere var hash string)\n");

		}
		//set_valor(busca(h, v->nome, v->escopo), valor);
	}
	return h;
}

Lista** insere_variavel_hash_vetor(Lista** h, Lista* l, float m){
	Lista* p;
	Variavel* v;
	for(p=l;p!=NULL;p=p->prox){
		v = (Variavel*)p->info;
		switch (v->tipo){
			case 0:
				set_valor(busca(h, v->nome, v->escopo), m);
				break;
			case 1: 
				set_valor(busca(h, v->nome, v->escopo), m);
				break;
			case 2:
				if (m != 0){
					set_valor_string(busca(h, v->nome, v->escopo), "verdadeiro");
				}
				else{
					set_valor_string(busca(h, v->nome, v->escopo), "falso");
				}
				break;
			default:
				printf("Fufu no switch (insere var hash valor)\n");

		}
		//set_valor(busca(h, v->nome, v->escopo), valor);
	}
	return h;
}

Lista** insere_variavel_hash_matriz(Lista** h, Lista* l, float m, float n){
	Lista* p;
	Variavel* v;
	for(p=l;p!=NULL;p=p->prox){
		v = (Variavel*)p->info;
		switch (v->tipo){
			case 0:
				set_valor(busca(h, v->nome, v->escopo), m);
				break;
			case 1: 
				set_valor(busca(h, v->nome, v->escopo), m);
				break;
			case 2:
				if (m != 0){
					set_valor_string(busca(h, v->nome, v->escopo), "verdadeiro");
				}
				else{
					set_valor_string(busca(h, v->nome, v->escopo), "falso");
				}
				break;
			default:
				printf("Fufu no switch (insere var hash valor)\n");

		}
		//set_valor(busca(h, v->nome, v->escopo), valor);
	}
	return h;
}

//insere uma variavel na tabela hash ESSE AQUI EH O BICHAO
Lista** insere_variavel (Lista** l, char nome[], int tipo, int usada, int escopo, int m, int n){
	int pos=0,i=0;
	char c;
	Lista* novo = (Lista*) malloc(sizeof(Lista));
	Variavel* var = (Variavel*) malloc (sizeof(Variavel));
	var->nome = (char*) malloc ((strlen(nome)+1)*sizeof(char));
	strcpy(var->nome,nome);
	if(busca(l,var->nome,escopo) != NULL){
		return NULL;
	}
	var->tipo = tipo;
	var->usada = usada;
	var->escopo = escopo;
	var->matriz[0] = m;
	var->matriz[1] = n;

	if(tipo == 0)
		var->valor = (int*) malloc(var->matriz[0]*var->matriz[1]*sizeof(int));
	else if(tipo == 1)
		var->valor = (char*) malloc(var->matriz[0]*var->matriz[1]*sizeof(char));
	else if(tipo == 2)
		var->valor = (char**) malloc(var->matriz[0]*var->matriz[1]*sizeof(char*));
	else if(tipo == 3)
		var->valor = (float*) malloc(var->matriz[0]*var->matriz[1]*sizeof(float));
	else if(tipo == 4)
		var->valor = (int*) malloc(var->matriz[0]*var->matriz[1]*sizeof(int));

	novo->info = var;
	novo->tipo = 0;
	c =nome[i];
	pos =pos+(int)c;
	i=1;
	while(c!='\0'){
		c=nome[i];
		pos=pos+(int)c;
		i++;
	}
	
	pos = pos%TAM;
	novo->prox = l[pos];
	
	l[pos] = novo;
	return l;
}

//insere a funcao em uma lista
Lista* insere_funcao_lista(Lista* l, char nome[]){
	Lista* novo = (Lista*) malloc(sizeof(Lista));
	Funcao* func = (Funcao*) malloc (sizeof(Funcao));
	func->nome = (char*) malloc ((strlen(nome)+1)*sizeof(char));
	strcpy(func->nome,nome);
	func->retorno = -1;
	func->aridade = -1;
	novo->info = func;
	novo->tipo = 1; // tipo == 1 é funcao
	novo->prox = l;
	l = novo;
	return l;
}



//insere uma lista de funcoes na tabela hash
Lista** insere_funcao_hash(Lista** h, Lista* l, int retorno, int aridade){
	Lista* p;
	Funcao* f = (Funcao*) malloc (sizeof(Funcao));
	char nome[100];
	
	for(p = l; p != NULL; p = p->prox){
		
		f = (Funcao*)p->info;
		strcpy(nome,f->nome);
		if(insere_funcao(h, nome, retorno, aridade) == NULL)
			return NULL;
		nome[0] = '\0';
	}
	return h;
}
//o vetor tipo_parametros tem q terminar com -1, que eh a para do while
Lista** insere_parametro_funcao(Lista** h, char nome[], int tipo_parametros[]){
	Lista *l;
	Funcao* f;
	int i=0;
	l = busca(h,nome,0);
	if(l!=NULL){
		f = (Funcao*)l->info;
		while(tipo_parametros[i]!=-1){
			f->tipo_parametros[i]=tipo_parametros[i];
			i++;
		}
		f->tipo_parametros[i]=-1;
	}
	return h;
	
	
}
//insere uma funcao na tabela hash
Lista** insere_funcao (Lista** l, char nome[], int retorno, int aridade){
	int pos=0,i=0;
	char c;
	Lista* novo = (Lista*) malloc(sizeof(Lista));
	Funcao* func = (Funcao*) malloc (sizeof(Funcao));
	func->nome = (char*) malloc (strlen(nome)*sizeof(char));
	strcpy(func->nome,nome);
	func->retorno = retorno;
	func->aridade = aridade;
	novo->info = func;
	novo->tipo = 1;

	c =nome[i];
	pos =pos+(int)c;
	while(c!='\0'){
		i++;	
		c=nome[i];
		pos=pos+(int)c;
	}
	pos = pos%TAM;
	novo->prox = l[pos];
	l[pos] = novo;
	return l;
}

void imprime_hash(Lista** l){
	int i;
	for(i=0;i<TAM;i++){
		if(l[i]!=NULL){
			imprime(l[i]);
		}	
	}
}
//imprime uma lista
void imprime (Lista* l){
	Lista* p;
	Variavel *v;
	Funcao *f;
	int i=0;
	if (l == NULL){
		printf("lista vazia!\n");
	}
	for (p=l; p!= NULL; p=p->prox){
		if(p->tipo == 0){
			v = (Variavel*)p->info;

			printf(" Variavel: nome = %s",v->nome);
			printf(" tipo = %d", v->tipo);
			printf(" usada = %d", v->usada);
			printf(" escopo = %d", v->escopo);
			if ( v->valor != NULL){
				switch(v->tipo){
					case 0:
						printf(" valor = %d", *(int*)v->valor);
						break;
					case 1: 
						printf(" valor = %.2f", *(float*)v->valor);
						break;
					case 2:
						printf(" valor = %s", (char*)v->valor);
						break;
					case 3:
						printf(" valor = %s", (char*)v->valor);
						break;
					case 4:
						printf(" valor = %s", (char*)v->valor);
						break;
				}
			}
			else {
				printf(" valor = NULL");
			}

			if (v->matriz[0] > 1 && v->matriz[1] > 1)
				printf(" Matriz: %d x %d", v->matriz[0], v->matriz[1]);
			else if (v->matriz[0] > 1)
				printf(" Vetor: %d", v->matriz[0]);
			printf("\n");
					
		}else if(p->tipo == 1){
			f = (Funcao*)p->info;
			printf(" Funcao: nome = %s retorno = %d aridade = %d --",f->nome, f->retorno, f->aridade);		
			while(f->tipo_parametros[i]!=-1){
				printf(" %d",f->tipo_parametros[i]);
				i++;
			}
			printf("\n");
		}
		i=0;
		
	}
}
//percorre a hash verificando se todas as variaveis foram utilizadas
void verifica_variavel_usada(Lista** l){
	int i;
	Lista* p;
	for(i=0;i<TAM;i++){
		if(l[i]!=NULL){
			//para cada posicao da hash que eh uma lista chama verifica
			verifica(l[i]);
		}	
	}
}
//percorre uma lista verificando se todas as variaveis foram utilizadas
void verifica (Lista* l){
	Lista* p;
	Variavel *v;
	for (p=l; p!= NULL; p=p->prox){
		
		if(p->tipo ==0){
			v = (Variavel*)p->info;
			if(v->usada == 0){
				printf(" Erro semantico: Variavel %s nao utilizada. Escopo: %d\n",v->nome, v->escopo);
				exit(0);
			}
		}
	}
}
//retorna o tipo da variavel
int get_tipo(Lista* l){
	Variavel *v;
	v=(Variavel*)l->info;
	return v->tipo;
}
float get_valor_float(Lista* l){
	Variavel *v;
	v = (Variavel*)l->info;
	//imprime(l);
	return *(float*)v->valor;
}
float get_valor_int(Lista* l){
	Variavel *v;
	v = (Variavel*)l->info;
	//printf("getvalorint\n");
	//imprime(l);
	return *(int*)v->valor;
}
char get_valor_char(Lista* l){
	Variavel *v;
	v = (Variavel*)l->info;
	//imprime(l);
	return *(char*)v->valor;
}
char* get_valor_string(Lista* l){
	Variavel *v;
	v = (Variavel*)l->info;
	//imprime(l);
	return (char*)v->valor;
}
int get_escopo(Lista* l){
	Variavel *v;
	v=(Variavel*)l->info;
	return v->escopo;
}

int get_usada(Lista* l){
	Variavel *v;
	v=(Variavel*)l->info;
	return v->usada;
}

char* get_nome(Lista* l){
	Variavel *v;
	v=(Variavel*)l->info;
	return v->nome;
}

int get_m(Lista* l){
	Variavel *v;
	v=(Variavel*)l->info;
	return v->matriz[0];
}

int get_n(Lista* l){
	Variavel *v;
	v=(Variavel*)l->info;
	return v->matriz[1];
}
//retorna a aridade da funcao
int get_aridade(Lista* l){
	Funcao *f;
	f=(Funcao*)l->info;
	return f->aridade;
}

int get_retorno(Lista* l){
	Funcao *f;
	f=(Funcao*)l->info;
	return f->retorno;
}

Arvore* insere_lista_arvore(Lista* l){
	Lista* p;
	Variavel* v;
	Arvore* a;
	Arvore* aux;
	Arvore* aux2;
	Arvore* aux3;
	int flag = 0;
	for(p=l;p!=NULL;p=p->prox){
		v = (Variavel*)p->info;
		
		if (flag == 0){	
			aux = cria_arvore("var",v->nome);
			a = aux;
			flag = 1;
		}
		else{
			
			if (flag == 1){
				aux2 = cria_arvore("var",v->nome);
				set_prox(aux,aux2);
				flag = 2;
			}
			else {
				aux3 = cria_arvore("var", v->nome);
				set_prox(aux2, aux3);
				aux2 = aux3;
			}
		}
	}
	a = aux;
	return a;
}