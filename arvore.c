#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "arvore.h"

struct arvore{
	char *tipo;
	char *valor;
	struct arvore *f1;
	struct arvore *f2;
	struct arvore *f3;	
	struct arvore *f4;
	struct arvore *prox;		
};

Arvore* inicializa_arvore (void){
	return NULL;
}
void set_tipo_arvore(Arvore *a,char tipo[]){
	strcpy(a->tipo,tipo);
}
void set_valor_arvore(Arvore *a,char valor[]){
	strcpy(a->valor,valor);
}
void set_f1(Arvore *a,Arvore *f1){
	a->f1 = f1;
}
void set_f2(Arvore *a,Arvore *f2){
	a->f2 = f2;
}
void set_f3(Arvore *a,Arvore *f3){
	a->f3 = f3;
}
void set_f4(Arvore *a,Arvore *f4){
	a->f4 = f4;
}
void set_prox(Arvore *a,Arvore *prox){
	a->prox = prox;
}

char* get_tipo_arvore(Arvore *a){
	return a->tipo;
}
char* get_valor_arvore(Arvore *a){
	return a->valor;
}
Arvore* get_f1(Arvore *a){
	return a->f1;
}
Arvore* get_f2(Arvore *a){
	return a->f2;
}
Arvore* get_f3(Arvore *a){
	return a->f3;
}
Arvore* get_f4(Arvore *a){
	return a->f4;
}
Arvore* get_prox(Arvore *a){
	return a->prox;
}

Arvore* get_final(Arvore *a){
	Arvore* aux = a;

	if (aux == NULL){
		return aux;
	}
	while(aux->prox!=NULL){
			aux = aux->prox;
	}
	return aux;
}

Arvore* cria_arvore(char tipo[], char valor[]){
	Arvore *a;
	a = (Arvore*) malloc(sizeof(Arvore));
	
	a->tipo = (char*) malloc ((strlen(tipo)+1)*sizeof(char)); 
	a->valor = (char*) malloc ((strlen(valor)+1)*sizeof(char));
	
	strcpy(a->tipo,tipo);
	strcpy(a->valor,valor);
	a->f1 = NULL;
	a->f2 = NULL;
	a->f3 = NULL;
	a->f4 = NULL;
	a->prox = NULL;
	
	return a;
	
}
Arvore* insere_arvore(Arvore *a, char tipo[], char valor[]){
	
	Arvore *arv;
	arv = (Arvore*) malloc(sizeof(Arvore));
	arv->tipo = (char*) malloc ((strlen(tipo)+1)*sizeof(char)); 
	arv->valor = (char*) malloc ((strlen(valor)+1)*sizeof(char));
	strcpy(arv->tipo,tipo);
	strcpy(arv->valor,valor);
	
	if (a->f1 == NULL)
		a->f1 = arv;
	else if (a->f2 == NULL)
		a->f2 = arv;
	else if (a->f3 == NULL)
		a->f3 = arv;
	else if (a->f4 == NULL)
		a->f4 = arv;			
	return a;
}
Arvore *insere_arvore_final(Arvore *final, Arvore *a){
	Arvore *aux;
	aux = final;
	if (aux == NULL){
		return a;
	}	
	else{	
		while(aux->prox!=NULL){
			aux = aux->prox;
		}
		aux->prox = a;
		return final;
	}
	
}
Arvore *insere_arvore_arvore(Arvore *arvore, Arvore *a){
	Arvore *aux;
	aux = arvore;
	
	if(aux->f1 == NULL)
		aux->f1 = a;
	else if(aux->f2 == NULL)
		aux->f2 = a;
	else if(aux->f3 == NULL)
		aux->f3 = a;
	else if(aux->f4 == NULL)
		aux->f4 = a;
	return aux;				
		
}


void arvore_imprime(Arvore* a){
       	if (a!=NULL){
       		printf("tipo: %s valor: %s\n", a->tipo, a->valor);
               	if(a->f1!=NULL){
               		printf("pai: %s f1 ->",a->valor);
               		arvore_imprime(a->f1);
               }
               if(a->f2!=NULL){
               		printf("pai: %s f2 ->",a->valor);
               		arvore_imprime(a->f2);
               	}
               	if(a->f3!=NULL){
					printf("pai: %s f3 ->",a->valor);
               		arvore_imprime(a->f3);
               	}
               	if(a->f4!=NULL){
               		printf("pai: %s f4 ->",a->valor);
               		arvore_imprime(a->f4);
       			}
       			if(a->prox!=NULL){ //TA FICANDO FEIO
               		printf("antes: %s prox: %s ", a->valor, a->prox->valor);
               		arvore_imprime(a->prox);
       			}
       }
}
void arvore_imprime_final(Arvore *a){
	Arvore *aux;
	for(aux=a;aux!=NULL;aux=aux->prox){
		arvore_imprime(aux);
	}
}


float executa_expressao(Arvore *a, Lista **tab_variaveis){
	float valor;
	Arvore *aux;
	Lista *var;
	aux = a;
	if((strcmp(aux->tipo,"expressao")==0) && (strcmp(aux->valor,"+")==0)){
		valor = executa_expressao(aux->f1,tab_variaveis) + executa_expressao(aux->f2,tab_variaveis);
	}
	else if((strcmp(aux->tipo,"expressao")==0) && (strcmp(aux->valor,"-")==0)){
		valor = executa_expressao(aux->f1,tab_variaveis) - executa_expressao(aux->f2,tab_variaveis);
	}
	else if((strcmp(aux->tipo,"expressao")==0) && (strcmp(aux->valor,"*")==0)){
		valor = executa_expressao(aux->f1,tab_variaveis) * executa_expressao(aux->f2,tab_variaveis);
	}
	else if((strcmp(aux->tipo,"expressao")==0) && (strcmp(aux->valor,"/")==0)){
		valor = executa_expressao(aux->f1,tab_variaveis) / executa_expressao(aux->f2,tab_variaveis);
	}
	else if((strcmp(aux->tipo,"inteiro")==0)){
		return atof(a->valor);
	}
	else if((strcmp(aux->tipo,"real")==0)){
		return atof(a->valor);
	}
	else if((strcmp(aux->tipo,"funcao")==0)){
		int ret;
		if(strcmp(aux->valor,"maximo")==0){
			ret = executa_maximo (aux,tab_variaveis);
		}
		if(strcmp(aux->valor,"minimo")==0){
			ret = executa_minimo (aux,tab_variaveis);
		}
		if(strcmp(aux->valor,"media")==0){
			ret = executa_media (aux,tab_variaveis);
		}
		return ret;
	}
	else if (strcmp(aux->tipo,"variavel")==0){
		
		var = busca(tab_variaveis,aux->valor, 0);
		if(get_tipo(var)==0)
			return get_valor_int(var);	
		else if(get_tipo(var)==3)
			return get_valor_float(var);	
	}
	return valor;

}

void executa_imprima(Arvore *a, Lista **tab_variaveis){
	Lista *l;
	
	
	l = busca (tab_variaveis, a->f1->valor, 0);
	if(get_tipo(l) == 0){
		int valor;
		valor = get_valor_int(l);
		printf("%d",valor);
	}
	if(get_tipo(l) == 1){
		char valor;
		valor = get_valor_char(l);
		printf("%c",valor);
	}
	if(get_tipo(l) == 2){
		char* valor;
		valor = get_valor_string(l);
		printf("%s",valor);
	}
	if(get_tipo(l) == 3){
		float valor;
		valor = get_valor_float(l);
		printf("%f",valor);
	}
}

void executa_imprima_ln(Arvore *a, Lista **tab_variaveis){
	Lista *l;
	
	
	l = busca (tab_variaveis, a->f1->valor, 0);
	if(get_tipo(l) == 0){
		int valor;
		valor = get_valor_int(l);
		printf("%d\n",valor);
	}
	if(get_tipo(l) == 1){
		char valor;
		valor = get_valor_char(l);
		printf("%c\n",valor);
	}
	if(get_tipo(l) == 2){
		char* valor;
		valor = get_valor_string(l);
		printf("%s\n",valor);
	}
	if(get_tipo(l) == 3){
		float valor;
		valor = get_valor_float(l);
		printf("%f\n",valor);
	}
}

void executa_leia(Arvore *a,Lista **tab_variaveis){
	printf("T1\n");
	Lista *l;
	printf("T2\n");
	l = busca (tab_variaveis, a->f1->valor, 0);
	printf("T3\n");
	if(get_tipo(l) == 0){
		int valor;
		scanf("%d",&valor);
		set_valor(l,valor);
	}
	if(get_tipo(l) == 1){
		char valor;
		scanf("%c",&valor);
		set_valor_string(l,&valor);
	}
	if(get_tipo(l) == 2){
		char* valor;
		scanf("%s",valor);
		set_valor_string(l,valor);
	}
	if(get_tipo(l) == 3){
		float valor;
		scanf("%f",&valor);
		set_valor(l,valor);
	}
}
Lista** executa_arvore(Arvore *a, Lista **tab_variaveis){
	//printf("tipo: %s valor: %s\n", a->tipo, a->valor);
	if (strcmp(a->tipo, "cmd") == 0){
		if(strcmp(a->valor,"atrib")==0){
			return executa_atrib(a,tab_variaveis);
		}
		else if (strcmp(a->valor, "se") == 0){
			executa_se(a, tab_variaveis);
		}
		return tab_variaveis;
	}
	else if(strcmp(a->tipo,"funcao")==0){
		if(strcmp(a->valor,"imprima")==0){
			executa_imprima(a,tab_variaveis);
			return tab_variaveis;
		}
		if(strcmp(a->valor,"imprima_ln")==0){
			executa_imprima_ln(a,tab_variaveis);
			return tab_variaveis;
		}
		if(strcmp(a->valor,"leia")==0){
			executa_leia(a,tab_variaveis);
			return tab_variaveis;
		}
		
	}
	//ir adicionando todas as funcoes de execucao que forem criadas	
}

void executa_arvore_final(Arvore *arvore_final, Lista **tab_variaveis){
	Arvore *aux;
	Lista **tab;
	tab = tab_variaveis;
	for(aux=arvore_final; aux!=NULL; aux=aux->prox){
		tab = executa_arvore(aux,tab);

	}
	
}
int executa_maximo(Arvore *a, Lista **tab){
	Lista *l1, *l2;
	l1 = busca(tab,a->f1->valor,0);
	l2 = busca(tab,a->f2->valor,0);
	if(get_valor_int(l1)>get_valor_int(l2)){
		return get_valor_int(l1);
	}
	else{
		return get_valor_int(l2);
	}
}
int executa_minimo(Arvore *a, Lista **tab){
	Lista *l1, *l2;
	l1 = busca(tab,a->f1->valor,0);
	l2 = busca(tab,a->f2->valor,0);
	if(get_valor_int(l1)<get_valor_int(l2)){
		return get_valor_int(l1);
	}
	else{
		return get_valor_int(l2);
	}
}
int executa_media(Arvore *a, Lista **tab){
	Lista *l1, *l2;
	l1 = busca(tab,a->f1->valor,0);
	l2 = busca(tab,a->f2->valor,0);
	return (get_valor_int(l1)+get_valor_int(l2))/2;
}

// a->f1 : variavel a qm atribuir
// a->f2 : valor da atribuicao
Lista** executa_atrib(Arvore* a, Lista** tab_var){
	Lista* l;
	Lista** tab = tab_var;
	l = busca(tab_var, a->f1->valor, 0); //buscando na tabela qm deve receber a atrib
	if (l == NULL){
		//Erro, variavel n encontrada
	}
	else {
		switch(get_tipo(l)){
			case 0:
				insere_variavel_hash_valor(tab, l, avaliaExpressaoInt(a->f2,tab,0));
				break;
			case 1:
				insere_variavel_hash_valor(tab, l, avaliaExpressaoFloat(a->f2,tab,0));
				break;
			case 2:
				insere_variavel_hash_valor(tab, l, avaliaExpressaoInt(a->f2,tab,0));
				break;
			case 3:
				insere_variavel_hash_string(tab, l, a->f2->valor);
				break;
			case 4:
				insere_variavel_hash_string(tab, l, a->f2->valor);
				break;
		}
	}

	return tab;

}


Lista** executa_atribuicao (Arvore *a,Lista **tab_variaveis){
	float valor, v;
	Arvore *aux;
	Lista *l;
	Lista **tab;
	tab = tab_variaveis;
	aux=a->f2;
	if((strcmp(aux->tipo,"int")==0) || (strcmp(aux->tipo,"real")==0)){
		valor = atof(aux->valor);
		l = busca (tab, a->f1->valor, 0);
		set_valor(l,valor);
		return tab;
	}
	else if ((strcmp(aux->tipo,"literal")==0) || (strcmp(aux->tipo,"caracter")==0)){
		char *str;
		str = (char*) malloc ((strlen(aux->valor)+1)*sizeof(char));
		strcpy(str,aux->valor);
		l = busca (tab, a->f1->valor, 0);
		set_valor_string(l,str);
		return tab;
	}
	else if ((strcmp(aux->tipo,"funcao")==0)){
		int ret;
		if(strcmp(aux->valor,"maximo")==0){
			ret = executa_maximo (aux,tab);
		}
		if(strcmp(aux->valor,"minimo")==0){
			ret = executa_minimo (aux,tab);
		}
		if(strcmp(aux->valor,"media")==0){
			ret = executa_media (aux,tab);
		}
		l = busca (tab, a->f1->valor, 0);
		set_valor(l,ret);
		return tab;
	}
	else{
		valor = executa_expressao(aux,tab);
	}
	l = busca (tab, a->f1->valor, 0);
	set_valor(l,valor);
	return tab;
}

//----------------------------------------------------------------------------------------------------------------

void executa_se(Arvore* arv, Lista **tab_var){
	Arvore* aux;
	aux = arv;
	Lista** tab = tab_var;
	if (avaliaExpressaoInt(aux->f1, tab, 0)){
		arvore_imprime(aux->f2);
		executa_arvore_final(aux->f2->f1, tab);
	}
	else {
		executa_arvore_final(aux->f3->f1, tab);
	}
}

Arvore* arvore_insereOp(char op, Arvore* v1, Arvore* v2){
	Arvore* a;

	//passar de char para char*
	char *ptr = malloc(2*sizeof(char));
	ptr[0] = op;
	ptr[1] = '\0';

	a = cria_arvore("op", ptr);

	set_f1(a, v2);
	set_f2(a, v1);

	return a;
}

Arvore* arvore_monta_exp(Pilha* p){
	Pilha *pval;
	pval = pilha_constroi(pval);
	Arvore* a, *b, *c;
	char *str = malloc(2*sizeof(char));
	int ass;
	
	while(!pilha_vazia(p)){
		if (get_doge(p) == 'n'){
			ass = get_tipo_pilha(p);
			sprintf(str, "%d", ass);
			pilha_plantar(pval, cria_arvore("int", str));
			pilha_putOut(p);
		} 
		else if(get_doge(p) == 'N'){
			sprintf(str, "%.2f", get_real(p));
			pilha_plantar(pval, cria_arvore("real", str));
			pilha_putOut(p);
		}
		else if(get_doge(p) == 'v'){
			pilha_plantar(pval, cria_arvore("var", get_var(p)));
			pilha_putOut(p);	
		}
		// eh op, entao tenho que montar arvore e resolver
		else if(get_doge(p) == '!'){
			b = pilha_desmatar(pval);
			a = arvore_insereOp(get_doge(p), NULL, b);
			pilha_plantar(pval, a);
			pilha_putOut(p);
		}
		else {
			b = pilha_desmatar(pval);
			c = pilha_desmatar(pval);
			a = arvore_insereOp(get_doge(p), b, c);
			pilha_plantar(pval, a);
			pilha_putOut(p);
		}
	}
	a = pilha_desmatar(pval);
	return a;
}

int avaliaExpressaoInt(Arvore *a, Lista** tabela_hash_var, int ESCOPO_VAR){
	// eh folha, ou seja, eh numero
	if (a->f1 == NULL && a->f2 == NULL){
		if (strcmp(a->tipo, "int") == 0) //eh int
			return atoi(a->valor); // fazer a conversao char pra int
		else if (strcmp(a->tipo, "var") == 0){ //eh var
			switch(get_tipo(busca(tabela_hash_var, a->valor, ESCOPO_VAR))){
				case 0: //inteiro
					return get_valor_int(busca(tabela_hash_var, a->valor, ESCOPO_VAR));
					break;
				case 1: //real
					return get_valor_float(busca(tabela_hash_var, a->valor, ESCOPO_VAR));
					break;
				case 2: //logico
					if (strcmp(get_valor_string(busca(tabela_hash_var, a->valor, ESCOPO_VAR)),"falso") == 0)
						return 0;
					else
						return 1;
					break;
				default:
					printf("That's NO good!\n");
					break;
			}
			return 0;
		} 
			
	}
	// eh no interno, calcular valor
	else {
		switch (a->valor[0]){
			case '^':
				return pow(avaliaExpressaoInt(a->f1, tabela_hash_var, ESCOPO_VAR), avaliaExpressaoInt(a->f2, tabela_hash_var, ESCOPO_VAR));
				break;
			case '*':
				return avaliaExpressaoInt(a->f1, tabela_hash_var, ESCOPO_VAR) * avaliaExpressaoInt(a->f2, tabela_hash_var, ESCOPO_VAR);
				break;
			case '/':
				return avaliaExpressaoInt(a->f1, tabela_hash_var, ESCOPO_VAR) / avaliaExpressaoInt(a->f2, tabela_hash_var, ESCOPO_VAR);
				break;
			case '%':
				return avaliaExpressaoInt(a->f1, tabela_hash_var, ESCOPO_VAR) % avaliaExpressaoInt(a->f2, tabela_hash_var, ESCOPO_VAR);
				break;
			case '+':
				return avaliaExpressaoInt(a->f1, tabela_hash_var, ESCOPO_VAR) + avaliaExpressaoInt(a->f2, tabela_hash_var, ESCOPO_VAR);
				break;
			case '-':
				return avaliaExpressaoInt(a->f1, tabela_hash_var, ESCOPO_VAR) - avaliaExpressaoInt(a->f2, tabela_hash_var, ESCOPO_VAR);
				break;
			case '&':
				return avaliaExpressaoInt(a->f1, tabela_hash_var, ESCOPO_VAR) && avaliaExpressaoInt(a->f2, tabela_hash_var, ESCOPO_VAR);
				break;
			case '|':
				return avaliaExpressaoInt(a->f1, tabela_hash_var, ESCOPO_VAR) || avaliaExpressaoInt(a->f2, tabela_hash_var, ESCOPO_VAR);
				break;
			case '!':
				return !avaliaExpressaoInt(a->f1, tabela_hash_var, ESCOPO_VAR);
			case '>':				
				return avaliaExpressaoInt(a->f1, tabela_hash_var, ESCOPO_VAR) > avaliaExpressaoInt(a->f2, tabela_hash_var, ESCOPO_VAR);
				break;
			case 'G':
				return avaliaExpressaoInt(a->f1, tabela_hash_var, ESCOPO_VAR) >= avaliaExpressaoInt(a->f2, tabela_hash_var, ESCOPO_VAR);
				break;
			case '<':
				return avaliaExpressaoInt(a->f1, tabela_hash_var, ESCOPO_VAR) < avaliaExpressaoInt(a->f2, tabela_hash_var, ESCOPO_VAR);
				break;
			case 'L':
				return avaliaExpressaoInt(a->f1, tabela_hash_var, ESCOPO_VAR) <= avaliaExpressaoInt(a->f2, tabela_hash_var, ESCOPO_VAR);
				break;
			case '=':
				return avaliaExpressaoInt(a->f1, tabela_hash_var, ESCOPO_VAR) == avaliaExpressaoInt(a->f2, tabela_hash_var, ESCOPO_VAR);
				break;
			case 'D':
				return avaliaExpressaoInt(a->f1, tabela_hash_var, ESCOPO_VAR) != avaliaExpressaoInt(a->f2, tabela_hash_var, ESCOPO_VAR);
				break;
			default:
				printf("Fodeu hard no switch!\n");
				break;
		}
	}
}

float avaliaExpressaoFloat(Arvore *a, Lista** tabela_hash_var, int ESCOPO_VAR){
	// eh folha, ou seja, eh numero
	if (a->f1 == NULL && a->f2 == NULL){
		if (strcmp(a->tipo, "real") == 0)
			return atof(a->valor); // fazer a conversao char pra real
		else if (strcmp(a->tipo, "var") == 0){ //eh var
			switch(get_tipo(busca(tabela_hash_var, a->valor, ESCOPO_VAR))){
				case 0: //inteiro
					return get_valor_int(busca(tabela_hash_var, a->valor, ESCOPO_VAR));
					break;
				case 1: //real
					return get_valor_float(busca(tabela_hash_var, a->valor, ESCOPO_VAR));
					break;
				case 2: //logico
					if (strcmp(get_valor_string(busca(tabela_hash_var, a->valor, ESCOPO_VAR)),"falso") == 0)
						return 0;
					else
						return 1;
					break;
				default:
					printf("That's NO good!\n");
					break;
			}
			return 0;
		}
	}
	// eh no interno, calcular valor
	else {
		switch (a->valor[0]){
			case '^':
				return pow(avaliaExpressaoFloat(a->f1, tabela_hash_var, ESCOPO_VAR), avaliaExpressaoFloat(a->f2, tabela_hash_var, ESCOPO_VAR));
				break;
			case '*':
				return avaliaExpressaoFloat(a->f1, tabela_hash_var, ESCOPO_VAR) * avaliaExpressaoFloat(a->f2, tabela_hash_var, ESCOPO_VAR);
				break;
			case '/':
				return avaliaExpressaoFloat(a->f1, tabela_hash_var, ESCOPO_VAR) / avaliaExpressaoFloat(a->f2, tabela_hash_var, ESCOPO_VAR);
				break;
			case '%':
				return (int)avaliaExpressaoFloat(a->f1, tabela_hash_var, ESCOPO_VAR) % (int)avaliaExpressaoFloat(a->f2, tabela_hash_var, ESCOPO_VAR);
				break;
			case '+':
				return avaliaExpressaoFloat(a->f1, tabela_hash_var, ESCOPO_VAR) + avaliaExpressaoFloat(a->f2, tabela_hash_var, ESCOPO_VAR);
				break;
			case '-':
				return avaliaExpressaoFloat(a->f1, tabela_hash_var, ESCOPO_VAR) - avaliaExpressaoFloat(a->f2, tabela_hash_var, ESCOPO_VAR);
				break;
			default:
				printf("Fodeu hard no switch!\n");
				break;
		}
	}
}

//---------------------------------------------------------------------------------------

struct arvore_pilha{
	Arvore *a;
	struct arvore_pilha *prox;		
};

Arvore* arvpilha_get_arvore(Arvore_pilha* p){
	return p->a;
}

Arvore_pilha* inicializa_arvpilha(){
	return NULL;
}

Arvore_pilha* insere_arvpilha(Arvore_pilha *pilha, Arvore *a){
	Arvore_pilha *nova;
	nova =  (Arvore_pilha*) malloc(sizeof(Arvore_pilha));

	nova->a = a;
	nova->prox = pilha;

	return nova;
	
}
Arvore_pilha *remove_arvpilha(Arvore_pilha *pilha){
	Arvore_pilha *aux;
	aux = pilha->prox;
	return aux;
}
Arvore *topo_arvpilha (Arvore_pilha *pilha){
	Arvore_pilha *p, *aux;
	Arvore *a;
	a = pilha->a;
	return a;
}

Arvore *remove_final_arvpilha (Arvore_pilha *pilha){
	Arvore_pilha *p, *aux;
	Arvore *a;
	for(aux=pilha; aux->prox->prox!=NULL; aux = aux->prox){

	}
	a = aux->prox->a;
	aux->prox =NULL;
	return a;
}

int tamanho_arvpilha(Arvore_pilha *pilha){
	Arvore_pilha *p;
	int tam=0;
	for(p=pilha; p!=NULL; p=p->prox){
		tam++;
	}
	return tam;
}
//sempre deve remover do final e inserindo no topo da pilha, ai quando pegar um operador remove os doi elementos do topo da pilha, cria a arvore e insere novamente na pilha, fazer isso ate sobrar um elemento
Arvore *monta_arvore_atribuicao(Arvore_pilha *pilha){
	Arvore *aux,*aux_f1,*aux_f2;
	int tam = 0;
	tam = tamanho_arvpilha(pilha);
	while(tam > 1){
		aux = remove_final_arvpilha(pilha);
		if(strcmp(aux->tipo,"expressao")==0){
			aux_f2 = topo_arvpilha(pilha);
			pilha = remove_arvpilha(pilha);
			aux_f1 = topo_arvpilha(pilha);
			pilha = remove_arvpilha(pilha);
			aux->f1 = aux_f1;
			aux->f2 = aux_f2;
			pilha = insere_arvpilha(pilha,aux);
		}
		else{
			pilha = insere_arvpilha(pilha,aux);
		}
		tam = tamanho_arvpilha(pilha);
	}
	return pilha->a;
}

void arvpilha_imprime(Arvore_pilha *a){
	Arvore_pilha *aux;
	
	for(aux=a; aux!=NULL;aux=aux->prox){
		arvore_imprime(aux->a);
	}
}

void leia(){
	int imprimir;
	fflush(stdin);
	printf("WOWOWOWOWWO\n");
	scanf(" %d ", &imprimir);
	printf("WOVVVVVVVVVVVVVVVVVVVVVVVVVVVv\n");
}
