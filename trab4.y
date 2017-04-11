%{
#include <stdio.h>
#include "arvore.h"

Lista *lista_var, *lista_func, *var, *func, *doge, *aux, *lista_atrib;
Lista **tabela_hash_var, **tabela_hash_func;
Pilha *pilha_termo, *pilha_op; //TERMO: 0 = int, 1 = real, 2 = logico, 3 = ident; OP: + = 0, - = 1, * = 2, / = 3, ^ = 4, and = 5, or = 6.
Pilha *pilha_infix; //pilha para ler a expressao infix (como ela eh digitada)
Pilha *pilha_posfix; //pilha para receber posfix
Pilha *pilha_final;
Pilha *pilha_teste;
Arvore *arvore_exp, *arvore_exp2, *arvore_teste, *arvore_final, *arvore_comp, *arvore_semifinal, *arvore_cmd, *arvore_listacmd, *arvore_doge, *arvore_doge2, *arvore_arg1, *arvore_arg2, *arvore_arg3, *arvore_string;
Arvore_pilha *comandos;
int qtd_param = 0;
char nome_func[100];
char nome_func2[100];
char nome_var[100];
int tipo_parametros[10];
float avaliado;
float avaliado2;
float resultado;
char op_comp;
char imprimir[100];
float arg1, arg2, arg3;
float arg[2];
char args[100];
int cont_arg = -1;
int leia_int;
float leia_float;
char leia_char;
char leia_string[100];
char op_arv_comp[2];
int pos_m, pos_n;

int ARIDADE_FUNC = 0;

extern int nlinhas;
extern char vlr_int[100];
extern char vlr_real[100];
extern char * yytext;
extern char ident[100];

int tipo_termos, tipo_operadores;
int TIPO_VAR = 0;
int TIPO_ATRIB = 0;
int TIPO_TERMO;
int TIPO_OP;
int ESCOPO_VAR = 0;
int flag_valorEhFuncao = 0; // VALOR era uma Chamada de Funcao 1
int flag_cmdChamada = 0; // Quando funcao eh chamada sozinha
int flag_ehMatriz = 0;
int flag_eh_arg = 0;
int flag_ehCMD = 0;
int flag_gambiarraAtrib = 0;
int flag_ehComparacao = 0;
int flag_first = 0;
int flag_cmd = 0;
int flag_arg_var = 0; // argumento eh variavel
int DIM_M, DIM_N = 1;


//Busca a variavel na tabela e 'seta' se eh usada ou se nao encontrar a variavel, erro.
void doge_var(Lista** tab, Lista* v, char* nom, int esc)
{ 
	v = busca(tab, nom, esc);
	if(v == NULL){
		printf(" Erro semantico: Variavel %s nao declarada. Escopo: %d, Linha: %d \n", nom, esc, nlinhas);
		exit(0);
		
	}else{
		set_usada(v);
	}
	v = inicializa(); 
}

%}

%token token_var_fim
%token token_var
%token token_char
%token token_algoritmo
%token token_if
%token token_do
%token token_do_end
%token token_strings
%token token_string
%token token_fim
%token token_else
%token token_while_end
%token token_matriz
%token token_booleans
%token token_boolean
%token token_or
%token token_then
%token token_for
%token token_for_end
%token token_ints
%token token_func
%token token_func_fim
%token token_int
%token token_inicio
%token token_and
%token token_if_end
%token token_then_end
%token token_else_end
%token token_de
%token token_ate
%token token_reals
%token token_return
%token token_real
%token token_not
%token token_while
%token token_chars
%token token_passo
%token token_print
%token token_read
%token token_central
%token token_minimo
%token token_maximo

%token token_aspas
%token token_atrib
%token token_maior
%token token_maior_igual
%token token_menor
%token token_menor_igual
%token token_igual
%token token_diferente
%token token_mais
%token token_menos
%token token_div
%token token_mult
%token token_pot
%token token_mod
%token token_increment
%token token_decrement

%token token_colchete_abre
%token token_colchete_fecha
%token token_abreParen
%token token_fechaParen
%token token_pt
%token token_virg
%token token_pt_virg
%token token_dois_pt
%token token_hashtag
%token token_chaves_abre
%token token_chaves_fecha
%token token_apost
%token token_cbarra

%token token_vlr_inteiro
%token token_vlr_real
%token token_vlr_char
%token token_true
%token token_false
%token token_ident
%token token_vlr_string

%start PROG

%%


PROG: 
	  token_algoritmo token_ident INSERE_INIT token_pt_virg BLOCO
	| token_algoritmo token_ident INSERE_INIT token_pt_virg ;

INSERE_INIT:{ 
	// inserindo o nome da main na tabela de variaveis
	tabela_hash_func = insere_funcao(tabela_hash_func, ident, -1, 0);
	tipo_parametros[0] = -1;
	insere_parametro_funcao(tabela_hash_func, ident, tipo_parametros);
	libera(lista_var);
	lista_var = inicializa();

	//inserindo as funcoes primitivas da linguagem na tabela de funcoes

	tabela_hash_func = insere_funcao(tabela_hash_func, "leia", -1, 0);
	tipo_parametros[0] = -1;
	insere_parametro_funcao(tabela_hash_func,"leia",tipo_parametros);

	tipo_parametros[0]=0;
	tipo_parametros[1]=-1;

	tabela_hash_func = insere_funcao(tabela_hash_func, "imprima", -1, 1);
	insere_parametro_funcao(tabela_hash_func,"imprima",tipo_parametros);

	tipo_parametros[0]=0;
	tipo_parametros[1]=0;
	tipo_parametros[2]=-1;

	tabela_hash_func = insere_funcao(tabela_hash_func, "maximo", 0, 2);
	insere_parametro_funcao(tabela_hash_func,"maximo",tipo_parametros);
	tabela_hash_func = insere_funcao(tabela_hash_func, "minimo", 0, 2);
	insere_parametro_funcao(tabela_hash_func,"minimo",tipo_parametros);
	tabela_hash_func = insere_funcao(tabela_hash_func, "%", 0, 2);
	insere_parametro_funcao(tabela_hash_func,"%",tipo_parametros);
	tabela_hash_func = insere_funcao(tabela_hash_func, "^", 0, 2);
	insere_parametro_funcao(tabela_hash_func,"^",tipo_parametros);
	tabela_hash_func = insere_funcao(tabela_hash_func, "+", 0, 2);
	insere_parametro_funcao(tabela_hash_func,"+",tipo_parametros);
	tabela_hash_func = insere_funcao(tabela_hash_func, "-", 0, 2);
	insere_parametro_funcao(tabela_hash_func,"-",tipo_parametros);
	tabela_hash_func = insere_funcao(tabela_hash_func, "*", 0, 2);
	insere_parametro_funcao(tabela_hash_func,"*",tipo_parametros);
	tabela_hash_func = insere_funcao(tabela_hash_func, "/", 0, 2);
	insere_parametro_funcao(tabela_hash_func,"/",tipo_parametros);

	tipo_parametros[2]=0;
	tipo_parametros[3]=-1;

	tabela_hash_func = insere_funcao(tabela_hash_func, "central", 0, 3);
	insere_parametro_funcao(tabela_hash_func,"central",tipo_parametros);
	
};

BLOCO:
	  DECL_VAR MAIS_FUNCOES { ESCOPO_VAR = 0; } BLOCO_MAIN 
	| BLOCO_MAIN
	| DECL_VAR BLOCO_MAIN
	| MAIS_FUNCOES { ESCOPO_VAR = 0; } BLOCO_MAIN ;

BLOCO_MAIN:
	  token_inicio LISTA_CMD {
	  	// desempilhar o ultimo sr. RSK
	  	printf("ANTES\n");
	  	arvore_listacmd = topo_arvpilha(comandos); 
	  	printf("QUASE DEPOIS\n");
	  	//arvore_imprime(arvore_listacmd);
	  	arvore_final = insere_arvore_arvore(arvore_final, arvore_listacmd);
	  	printf("DEPOIS\n");
	  } token_fim
	| token_inicio token_fim ;

DECL_VAR:
	  token_var LISTA_VAR token_var_fim
	| token_var token_var_fim;

MAIS_FUNCOES:
	  MAIS_FUNCOES DECL_FUNC token_func_fim
	| DECL_FUNC token_func_fim ;

LISTA_VAR:
	  LISTA_VAR REC_IDENT token_dois_pt TIPO COD1 token_pt_virg 
	| REC_IDENT token_dois_pt TIPO COD1 token_pt_virg ;

COD1: {
	if (flag_ehMatriz == 0) {
		DIM_M = 1;
		DIM_N = 1;
		insere_variavel_hash(tabela_hash_var, lista_var, TIPO_VAR, ESCOPO_VAR); 
	}
	else {
		edita_para_matriz(lista_var, DIM_M, DIM_N);
		insere_variavel_hash(tabela_hash_var, lista_var, TIPO_VAR, ESCOPO_VAR);
		DIM_M = 1;
		DIM_N = 1;
	}
	libera(lista_var);
	lista_var = inicializa();
} ;

REC_IDENT: 
	  REC_IDENT token_virg token_ident { lista_var = insere_variavel_lista(lista_var, ident,0); }
	| token_ident { lista_var = insere_variavel_lista(lista_var, ident,0); } ;

BLOCO_FUNC:
	  DECL_VAR BLOCO_MAIN 
	| BLOCO_MAIN;

DECL_FUNC: 
	  token_func token_ident STRCPY_FUNC PARAMETROS token_dois_pt TIPO INSERE_FUNC_TAB token_pt_virg BLOCO_FUNC
	| token_func token_ident STRCPY_FUNC PARAMETROS INSERE_PROC_TAB token_pt_virg BLOCO_FUNC 
	| token_func token_ident STRCPY_FUNC PARAMETROS token_dois_pt TIPO INSERE_FUNC_TAB token_pt_virg
	| token_func token_ident STRCPY_FUNC PARAMETROS INSERE_PROC_TAB token_pt_virg ;

STRCPY_FUNC: { strcpy(nome_func, ident); strcpy(nome_func2, nome_func); ESCOPO_VAR++;} ;

INSERE_FUNC_TAB: {
	func = busca(tabela_hash_func, nome_func, ESCOPO_VAR);
	if(func) {
		printf(" Erro semantico: Funcao %s redeclarada. Escopo: %d, Linha: %d \n", nome_func, ESCOPO_VAR, nlinhas);
		exit(0);
	}
	tabela_hash_func = insere_funcao(tabela_hash_func, nome_func, TIPO_VAR, qtd_param); // TIPO_VAR eh o tipo de retorno da funcao
	tipo_parametros[qtd_param] = -1;
	tabela_hash_func = insere_parametro_funcao(tabela_hash_func, nome_func, tipo_parametros);
	qtd_param = 0;
};

INSERE_PROC_TAB: {
	func = busca(tabela_hash_func, nome_func, ESCOPO_VAR);
	if(func) {
		printf(" Erro semantico: Funcao %s redeclarada. Escopo: %d, Linha: %d \n", nome_func, ESCOPO_VAR, nlinhas);
		exit(0);
	}
	tabela_hash_func = insere_funcao(tabela_hash_func, nome_func, -1, qtd_param); // -1 eh o TIPO_VAR para funcoes que nao tem retorno, ou seja, para procedimentos
	tipo_parametros[qtd_param] = -1;
	tabela_hash_func = insere_parametro_funcao(tabela_hash_func, nome_func, tipo_parametros);
	qtd_param = 0;
};

PARAMETROS:
	  token_abreParen LISTA_PARAM token_fechaParen
	| token_abreParen token_fechaParen;

LISTA_PARAM:
	  LISTA_PARAM token_virg token_ident INSERE_VAR_LISTAPARAM token_dois_pt TIPO INSERE_LISTAPARAM_HASH
	| token_ident INSERE_VAR_LISTAPARAM token_dois_pt TIPO INSERE_LISTAPARAM_HASH ;

INSERE_VAR_LISTAPARAM: { 
	strcpy(nome_var, yytext); 
	lista_var = insere_variavel_lista(lista_var, yytext, 0); 
	qtd_param++; 
};

INSERE_LISTAPARAM_HASH: { 
	insere_variavel_hash(tabela_hash_var, lista_var, TIPO_VAR, ESCOPO_VAR); 
	doge_var(tabela_hash_var, var, nome_var, 0); 
	libera(lista_var); 
	lista_var = inicializa(); 
	tipo_parametros[qtd_param -1] = TIPO_VAR;
};

//-------------------------------------------------------------------------------------------------------------

LISTA_CMD: {
		// 
	} REP_CMD ;

REP_CMD: 
	  REP_CMD CMD {
	  	// inserir no topo da pilha "comandos"
	  	// TESTE: passar "arvore_cmd = NULL" e mandar inserir pra ver o que da
	  	arvore_listacmd = topo_arvpilha(comandos);
	  	arvore_listacmd = insere_arvore_final(arvore_listacmd, arvore_cmd);
	  	printf("MERDA\n");
	  	arvore_imprime(arvore_cmd); // AQUI HEHEHE arvore_cmd esta errado
	}
	| CMD {
		// empilhar arvore_cmd (pq aqui ele eh o primeiro comando de um bloco de comandos)
		comandos = insere_arvpilha(comandos, arvore_cmd);
		printf("CANCER INICIAL\n");
		arvore_imprime(arvore_cmd);
	} ;

// Apos "CMD" ter sido realizado, devemos ter arvore_cmd apontando para um no' de arvore completo, contendo sua arvore de execucao
CMD: 
	  CMD_WHILE 
	| CMD_DO_WHILE 
	| CMD_FOR 
	| CMD_SIMPLES token_pt_virg 
	| CMD_IF  ;

CMD_IF: 
	  token_if COD_IF1 ARV_EXPRESSAO COD_IF2 token_then LISTA_CMD COD_IF3 token_then_end {arvore_cmd = arvore_doge;} // loop aqui provavelmente
	| token_if COD_IF1 ARV_EXPRESSAO COD_IF2 token_then LISTA_CMD COD_IF3 token_then_end token_else LISTA_CMD COD_IF4 token_else_end {arvore_cmd = arvore_doge;};

COD_IF1: {
	flag_ehCMD = 1; // setando a flag p/ n zoar verificacao de tipos na atribuicao
	// criar no' "se": (tipo: "cmd", valor: "se") [arvore_cmd = "se"]
	// e inserir esse no' no topo atual da pilha
	arvore_doge = cria_arvore("cmd", "se");
};

COD_IF2:{
	flag_ehCMD = 0; // resetando a flag p/ n zoar verificacao de tipos na atribuicao
	// inserir arvore de expressao no no' criado acima (em f1)
	if (flag_ehComparacao == 1){
		arvore_doge = insere_arvore_arvore(arvore_doge, arvore_comp);
	} else {
		arvore_doge = insere_arvore_arvore(arvore_doge, arvore_exp);
	}
	flag_ehComparacao = 0;
	
	// GHJ - arvore_doge esta' certo
	// preparacao para o then 
	// inserir esse no' criado acima no final do topo da pilha p/ depois comecar o bloco do then
	arvore_listacmd = topo_arvpilha(comandos);
	arvore_listacmd = insere_arvore_final(topo_arvpilha(comandos), arvore_doge);
	printf("EOQ\n");
	arvore_imprime(arvore_listacmd); // arvore_listacmd esta' errado
};

COD_IF3: {
	// agora a pilha tem um no' extra empilhado no topo, o no' do "entao"
	// desempilhar o no' "entao" da lista de comandos e inserir no no' criado acima (em f2) [arvore_cmd = "entao", ultimo elemento de arvore_listacmd = arvore_doge = "se"]
	arvore_cmd = arvpilha_get_arvore(remove_arvpilha(comandos));
	arvore_listacmd = topo_arvpilha(comandos); // tem que ser depois de remover, senao ele pega o topo do entao e da loop infinito
	arvore_doge = get_final(arvore_listacmd);
	arvore_doge = insere_arvore_arvore(arvore_doge, arvore_cmd);

};

COD_IF4:{
	// mesmo procedimento que o "entao"
	// agora a pilha tem um no' extra empilhado no topo, o no' do "senao"
	// desempilhar o no' "senao" da lista de comandos e inserir no no' criado acima (em f3) [arvore_cmd = "senao", ultimo elemento de arvore_listacmd = arvore_doge = "se"]
	arvore_cmd = arvpilha_get_arvore(remove_arvpilha(comandos));
	arvore_listacmd = topo_arvpilha(comandos); // tem que ser depois de remover, senao ele pega o topo do entao e da loop infinito
	arvore_doge = get_final(arvore_listacmd);
	arvore_doge = insere_arvore_arvore(arvore_doge, arvore_cmd);
}; 

CMD_DO_WHILE: token_do LISTA_CMD token_do_end token_while ARV_EXPRESSAO ;

CMD_WHILE:
	  token_while ARV_EXPRESSAO token_do LISTA_CMD token_while_end
	| token_while ARV_EXPRESSAO token_do token_while_end ;

CMD_FOR:
	 token_for TK_IDENT token_de IDENT_OU_INT token_ate IDENT_OU_INT token_do LISTA_CMD token_for_end
       | token_for TK_IDENT token_de IDENT_OU_INT token_ate IDENT_OU_INT token_passo IDENT_OU_INT token_do LISTA_CMD token_for_end
       | token_for TK_IDENT token_de IDENT_OU_INT token_ate IDENT_OU_INT token_do token_for_end
       | token_for TK_IDENT token_de IDENT_OU_INT token_ate IDENT_OU_INT token_passo IDENT_OU_INT token_do token_for_end ;

IDENT_OU_INT: 
	  TK_IDENT { flag_arg_var = 1;}
	| token_vlr_inteiro { arg[cont_arg] = atoi(vlr_int); }
	| token_menos token_vlr_inteiro { arg[cont_arg] = -1*atoi(vlr_int); } ;

CMD_SIMPLES: 
	  ATRIB {arvore_cmd = arvore_teste; }
	| CHAMADA_FUNCAO {
		  if (get_retorno(busca(tabela_hash_func, nome_func, ESCOPO_VAR)) != -1){
			 printf(" Erro semantico: Funcao com retorno porem sem atribuicao. Funcao: %s, Linha: %d\n", nome_func, nlinhas); 
			exit(0);	
		}
	}
	| CMD_IMPRIMA
	| CMD_MINIMO
	| CMD_MAXIMO
	| CMD_CENTRAL
	| RETURN 
    | OP_INCR;

//-------------------------------------------------------------------------------------------------------------
ATRIB: IDENTS 
	{ 	TIPO_ATRIB = get_tipo(busca(tabela_hash_var,nome_var,ESCOPO_VAR));
		if (TIPO_ATRIB == 1){
			while(flag_gambiarraAtrib != 0){
				pilha_tira(pilha_infix);
				flag_gambiarraAtrib--;
			}	
		}
		else {
			while(flag_gambiarraAtrib != 0){
				pilha_remove(pilha_infix);
				flag_gambiarraAtrib--;
			}
		}
	} 
	token_atrib VALOR { 
	if (flag_valorEhFuncao == 1){
		if(TIPO_ATRIB != get_retorno(busca(tabela_hash_func, nome_func, ESCOPO_VAR))){
			printf(" Erro semantico: Funcao com tipo de retorno incompativel. Funcao: %s, Linha: %d. \n", nome_func, nlinhas);
			exit(0);
		}
		flag_valorEhFuncao = 0;
	}
	
	//imprime_hash(tabela_hash_var);
	if (flag_ehComparacao == 1){
		if (flag_ehCMD == 1){

		}
		else if (TIPO_ATRIB == 3 || TIPO_ATRIB == 4){

		}
		else if (TIPO_ATRIB != 2){
			printf(" Erro semantico: Incompatibilidade de tipos na atribuicao. Linha: %d.\n", nlinhas);
			exit(0);	
		} else {
			//insere_variavel_hash_valor(tabela_hash_var, lista_atrib, resultado); //ir para execucao
			arvore_teste = cria_arvore("cmd", "atrib");
			arvore_teste = insere_arvore_arvore(arvore_teste, insere_lista_arvore(lista_atrib)); //insere F1

			arvore_teste = insere_arvore_arvore(arvore_teste, arvore_comp); //F2
		}
	}
	else {
		if (TIPO_ATRIB == 3 || TIPO_ATRIB == 4){

		}
		//insere_variavel_hash_valor(tabela_hash_var, lista_atrib, avaliado); //ir para execucao
		else {
			arvore_teste = cria_arvore("cmd", "atrib");
			arvore_teste = insere_arvore_arvore(arvore_teste, insere_lista_arvore(lista_atrib)); //insere F1

			arvore_teste = insere_arvore_arvore(arvore_teste, arvore_exp); //Insere F2
		}
	}
	libera(lista_atrib);
	lista_atrib = inicializa();
	flag_ehComparacao = 0;
	flag_gambiarraAtrib = 0;
};

IDENTS: 
	  IDENTS token_virg TK_IDENT INSERIR_VARS_LISTA
	| TK_IDENT INSERIR_VARS_LISTA;

INSERIR_VARS_LISTA: {
	doge_var(tabela_hash_var, var, nome_var, ESCOPO_VAR);
	lista_atrib = insere_variavel_lista1(lista_atrib, ident, get_tipo(busca(tabela_hash_var, ident, ESCOPO_VAR)), ESCOPO_VAR, 1); 
}

CMD_IMPRIMA: token_print token_abreParen ARG {flag_eh_arg = 0;} token_fechaParen {

	arvore_teste = cria_arvore("funcao","imprima");
	arvore_teste = insere_arvore(arvore_teste,"imp",imprimir);
	arvore_final = insere_arvore_final(arvore_final, arvore_teste);

	//execucao
	if (flag_arg_var == 1){
		switch (get_tipo(busca(tabela_hash_var, get_valor_arvore(get_f1(arvore_teste)), ESCOPO_VAR))){
			case 0: //inteiro
				printf("IMPRIMA: %.0f\n", get_valor_int(busca(tabela_hash_var, get_valor_arvore(get_f1(arvore_teste)), ESCOPO_VAR)));
				break;
			case 1: //real
				printf("IMPRIMA: %.2f\n", get_valor_float(busca(tabela_hash_var, get_valor_arvore(get_f1(arvore_teste)), ESCOPO_VAR)));
				break;
			case 2: //logico
				printf("IMPRIMA: %s\n", get_valor_string(busca(tabela_hash_var, get_valor_arvore(get_f1(arvore_teste)), ESCOPO_VAR)));
				break;
			case 3: //caracter
				printf("IMPRIMA: %c\n", get_valor_char(busca(tabela_hash_var, get_valor_arvore(get_f1(arvore_teste)), ESCOPO_VAR)));
				break;
			case 4: //literal
				printf("IMPRIMA: %s\n", get_valor_string(busca(tabela_hash_var, get_valor_arvore(get_f1(arvore_teste)), ESCOPO_VAR)));
				break;
			}
	}
	else {
		printf("IMPRIMA: %s\n", imprimir);	
	}

	flag_arg_var = 0;
	
} ;

ARG: 
	  ARG token_virg {flag_eh_arg = 1;} VALOR VERIFICA_VAR_DECLARADA
	| {flag_eh_arg = 1;} VALOR VERIFICA_VAR_DECLARADA ;

VERIFICA_VAR_DECLARADA: {
	var = busca(tabela_hash_var,ident,ESCOPO_VAR);
	if (var == NULL)
		{
			printf(" Erro semantico: Variavel %s nao declarada. Linha: %d.\n", ident, nlinhas);
			exit(0);
		}
	doge = insere_variavel_lista1(doge,ident,get_tipo(var),get_escopo(var),get_usada(var));
	qtd_param++;
};

CMD_CENTRAL: token_central token_abreParen { cont_arg = 0; } IDENT_OU_NUM {
 		arvore_teste = cria_arvore("funcao","central");
		if (flag_arg_var == 1){ //eh variavel
			arvore_arg1 = cria_arvore("var", args);
		}
		else {
			sprintf(args, "%.2f", arg[0]);
			arvore_arg1 = cria_arvore("num", args);		
		}
		flag_arg_var = 0; 
		cont_arg = 1; 
 	} token_virg IDENT_OU_NUM {
 		if (flag_arg_var == 1){
			arvore_arg2 = cria_arvore("var", args);	
		}
		else {
			sprintf(args, "%.2f", arg[1]);
			arvore_arg2 = cria_arvore("num", args);	
		}
 		cont_arg = 2; 
 	} token_virg IDENT_OU_NUM token_fechaParen {
 		if (flag_arg_var == 1){
			arvore_arg3 = cria_arvore("var", args);	
		}
		else {
			sprintf(args, "%.2f", arg[2]);
			arvore_arg3 = cria_arvore("num", args);	
		}

		set_f1(arvore_teste, arvore_arg1);
		set_f2(arvore_teste, arvore_arg2);
		set_f3(arvore_teste, arvore_arg3);
		arvore_final = insere_arvore_final(arvore_final, arvore_teste);

		//execucao
		if (strcmp(get_tipo_arvore(get_f1(arvore_teste)),"var") == 0){
			if (get_tipo(busca(tabela_hash_var, get_valor_arvore(get_f1(arvore_teste)), ESCOPO_VAR)) == 1){
				arg[0] = get_valor_float(busca(tabela_hash_var, get_valor_arvore(get_f1(arvore_teste)), ESCOPO_VAR));	
			}
			else{
				arg[0] = get_valor_int(busca(tabela_hash_var, get_valor_arvore(get_f1(arvore_teste)), ESCOPO_VAR));	
			}
		}
		else {
			arg[0] = atof(get_valor_arvore(get_f1(arvore_teste)));
		}

		if (strcmp(get_tipo_arvore(get_f2(arvore_teste)),"var") == 0){
			if (get_tipo(busca(tabela_hash_var, get_valor_arvore(get_f2(arvore_teste)), ESCOPO_VAR)) == 1){
				arg[1] = get_valor_float(busca(tabela_hash_var, get_valor_arvore(get_f2(arvore_teste)), ESCOPO_VAR));	
			}
			else{
				arg[1] = get_valor_int(busca(tabela_hash_var, get_valor_arvore(get_f2(arvore_teste)), ESCOPO_VAR));	
			}
		}
		else {
			arg[1] = atof(get_valor_arvore(get_f2(arvore_teste)));
		}

		if (strcmp(get_tipo_arvore(get_f3(arvore_teste)),"var") == 0){
			if (get_tipo(busca(tabela_hash_var, get_valor_arvore(get_f3(arvore_teste)), ESCOPO_VAR)) == 1){
				arg[2] = get_valor_float(busca(tabela_hash_var, get_valor_arvore(get_f3(arvore_teste)), ESCOPO_VAR));	
			}
			else{
				arg[2] = get_valor_int(busca(tabela_hash_var, get_valor_arvore(get_f3(arvore_teste)), ESCOPO_VAR));	
			}
		}
		else {
			arg[2] = atof(get_valor_arvore(get_f2(arvore_teste)));
		}

		if (arg[0] >= arg[1]){
			if (arg[0] >= arg[2]){
				if (arg[1] >= arg[2]){
					printf("CENTRAL: %.2f \n", arg[1]);
				}
				else{
					printf("CENTRAL: %.2f \n", arg[2]);	
				}
			}
			else{
				printf("CENTRAL: %.2f \n", arg[0]);
			}
		}
		else if (arg[0] >= arg[2]){
			printf("CENTRAL: %.2f \n", arg[0]);
		}
		else if (arg[1] >= arg[2]) {
			printf("CENTRAL: %.2f \n", arg[2]);
		}
		else {
			printf("CENTRAL: %.2f \n", arg[1]);
		}
		cont_arg = -1;
};

IDENT_OU_NUM: IDENT_OU_INT 
			| token_vlr_real { arg[cont_arg] = atof(vlr_real); }
			| token_menos token_vlr_real { arg[cont_arg] = -1*atof(vlr_real); };

CMD_MINIMO: token_minimo token_abreParen { cont_arg = 0; } IDENT_OU_NUM { 
		arvore_teste = cria_arvore("funcao","minimo");
		if (flag_arg_var == 1){ //eh variavel
			arvore_arg1 = cria_arvore("var", args);
		}
		else {
			sprintf(args, "%.2f", arg[0]);
			arvore_arg1 = cria_arvore("num", args);		
		}
		flag_arg_var = 0; 
		cont_arg = 1; 
	} token_virg IDENT_OU_NUM token_fechaParen {
	
		if (flag_arg_var == 1){
			arvore_arg2 = cria_arvore("var", args);	
		}
		else {
			sprintf(args, "%.2f", arg[1]);
			arvore_arg2 = cria_arvore("num", args);	
		}

		set_f1(arvore_teste, arvore_arg1);
		set_f2(arvore_teste, arvore_arg2);
		arvore_final = insere_arvore_final(arvore_final, arvore_teste);

		//execucao
		if (strcmp(get_tipo_arvore(get_f1(arvore_teste)),"var") == 0){
			if (get_tipo(busca(tabela_hash_var, get_valor_arvore(get_f1(arvore_teste)), ESCOPO_VAR)) == 1){
				arg[0] = get_valor_float(busca(tabela_hash_var, get_valor_arvore(get_f1(arvore_teste)), ESCOPO_VAR));	
			}
			else{
				arg[0] = get_valor_int(busca(tabela_hash_var, get_valor_arvore(get_f1(arvore_teste)), ESCOPO_VAR));	
			}
		}
		else {
			arg[0] = atof(get_valor_arvore(get_f1(arvore_teste)));
		}

		if (strcmp(get_tipo_arvore(get_f2(arvore_teste)),"var") == 0){
			if (get_tipo(busca(tabela_hash_var, get_valor_arvore(get_f2(arvore_teste)), ESCOPO_VAR)) == 1){
				arg[1] = get_valor_float(busca(tabela_hash_var, get_valor_arvore(get_f2(arvore_teste)), ESCOPO_VAR));	
			}
			else{
				arg[1] = get_valor_int(busca(tabela_hash_var, get_valor_arvore(get_f2(arvore_teste)), ESCOPO_VAR));	
			}
		}
		else {
			arg[1] = atof(get_valor_arvore(get_f2(arvore_teste)));
		}

		if (arg[0] <= arg[1]){
			printf("MINIMO: %.2f \n", arg[0]);
		}
		else {
			printf("MINIMO: %.2f \n", arg[1]);
		}
		cont_arg = -1;
};

CMD_MAXIMO: token_maximo token_abreParen { cont_arg = 0; } IDENT_OU_NUM { 
		arvore_teste = cria_arvore("funcao","maximo");
		if (flag_arg_var == 1){ //eh variavel
			arvore_arg1 = cria_arvore("var", args);
		}
		else {
			sprintf(args, "%.2f", arg[0]);
			arvore_arg1 = cria_arvore("num", args);		
		}
		flag_arg_var = 0; 
		cont_arg = 1;  
	} token_virg IDENT_OU_NUM token_fechaParen {

		if (flag_arg_var == 1){
				arvore_arg2 = cria_arvore("var", args);	
			}
			else {
				sprintf(args, "%.2f", arg[1]);
				arvore_arg2 = cria_arvore("num", args);	
			}

			set_f1(arvore_teste, arvore_arg1);
			set_f2(arvore_teste, arvore_arg2);
			arvore_final = insere_arvore_final(arvore_final, arvore_teste);

			//execucao
			if (strcmp(get_tipo_arvore(get_f1(arvore_teste)),"var") == 0){
				if (get_tipo(busca(tabela_hash_var, get_valor_arvore(get_f1(arvore_teste)), ESCOPO_VAR)) == 1){
					arg[0] = get_valor_float(busca(tabela_hash_var, get_valor_arvore(get_f1(arvore_teste)), ESCOPO_VAR));	
				}
				else{
					arg[0] = get_valor_int(busca(tabela_hash_var, get_valor_arvore(get_f1(arvore_teste)), ESCOPO_VAR));	
				}
			}
			else {
				arg[0] = atof(get_valor_arvore(get_f1(arvore_teste)));
			}

			if (strcmp(get_tipo_arvore(get_f2(arvore_teste)),"var") == 0){
				if (get_tipo(busca(tabela_hash_var, get_valor_arvore(get_f2(arvore_teste)), ESCOPO_VAR)) == 1){
					arg[1] = get_valor_float(busca(tabela_hash_var, get_valor_arvore(get_f2(arvore_teste)), ESCOPO_VAR));	
				}
				else{
					arg[1] = get_valor_int(busca(tabela_hash_var, get_valor_arvore(get_f2(arvore_teste)), ESCOPO_VAR));	
				}
			}
			else {
				arg[1] = atof(get_valor_arvore(get_f2(arvore_teste)));
			}

			if (arg[0] >= arg[1]){
				printf("MAXIMO: %.2f \n", arg[0]);
			}
			else {
				printf("MAXIMO: %.2f \n", arg[1]);
			}
			cont_arg = -1;
};

RETURN: token_return ARV_EXPRESSAO {flag_valorEhFuncao = 0;} ;

STRCPY_IDENT: token_ident { strcpy(nome_func, ident); } ;

CHAMADA_FUNCAO: 
	STRCPY_IDENT token_abreParen ARG { flag_eh_arg = 0; } token_fechaParen
	{	
		func = busca(tabela_hash_func, nome_func, ESCOPO_VAR);
		if (func == NULL){
				printf(" Erro semantico: Funcao nao declarada. Funcao: %s, Linha: %d.\n", nome_func, nlinhas);
				exit(0);
		}
		if (get_aridade(func) != qtd_param){
				printf(" Erro semantico: Quantidade de parametros errada. Funcao %s, Linha: %d.\n", nome_func, nlinhas);
				exit(0);
		}
		if (verifica_tipo_parametros_funcao(tabela_hash_func, nome_func, doge) == 0){
				printf(" Erro semantico: Tipo de parametros errado. Funcao: %s, Linha: %d.\n", nome_func, nlinhas);			
				exit(0);
		}
		qtd_param = 0;
		doge = inicializa();	
	}
	| STRCPY_IDENT token_abreParen token_fechaParen { 
		strcpy(nome_func, ident);
		func = busca(tabela_hash_func, nome_func, ESCOPO_VAR);
		if (func == NULL){
				printf(" Erro semantico: Funcao nao declarada. Funcao: %s, Linha: %d.\n", nome_func, nlinhas);
				exit(0);
		}
		if (get_aridade(func) > 0){
				printf(" Erro semantico: Quantidade de parametros errada. Funcao: %s, Linha: %d.\n", nome_func, nlinhas);
				exit(0);
		}
	};

//-------------------------------------------------------------------------------------------------------------

TIPO: 
	  TIPO_PRIM {flag_ehMatriz = 0;}
	| MATRIZ ;

MATRIZ: token_matriz T_MAT token_de TIPO_PRIM {flag_ehMatriz = 1;} ;

T_MAT: 
	  token_colchete_abre token_vlr_inteiro SALVAR_M token_colchete_fecha token_colchete_abre token_vlr_inteiro SALVAR_N token_colchete_fecha // MATRIZ
    | token_colchete_abre token_vlr_inteiro SALVAR_M token_colchete_fecha ;  // VETOR 

SALVAR_M: {
	// if (flag_eh_atrib == 1){
	// 	pos_m = atoi(vlr_int);
	// }
	DIM_M = atoi(vlr_int);
} ;

SALVAR_N: {
	// if (flag_eh_atrib == 1){
	// 	pos_m = atoi(vlr_int);
	// }
	DIM_N = atoi(vlr_int);
} ;

TIPO_PRIM: 
	  token_int {TIPO_VAR = 0; }
	| token_char {TIPO_VAR = 3; }
	| token_string {TIPO_VAR = 4; }
	| token_real {TIPO_VAR = 1; }
	| token_boolean {TIPO_VAR = 2; } ;

VALOR: 
	ARV_EXPRESSAO 
	{
		strcpy(imprimir, nome_var);
		flag_arg_var = 1;
		tipo_operadores =  pilha_remove(pilha_op);
		tipo_termos = pilha_remove(pilha_termo);
		if (tipo_operadores == 0){
			if (!(tipo_termos == 0 || tipo_termos == 1)){
				printf(" Erro semantico: Incompatibilidade na expressao. Linha: %d.\n", nlinhas ); 
				exit(0);
			}
		}
		if (tipo_operadores == 1){
			if (tipo_termos != 2){
				printf(" Erro semantico: Incompatibilidade na expressao. Linha: %d.\n", nlinhas ); 
				exit(0);
			}
		}
		if(flag_eh_arg == 0){
			if (flag_ehComparacao == 1){
				// eh comparacao, deixar prosseguir
				
			}
			else {
				if(TIPO_ATRIB != tipo_termos){ //tipo_expressao
					printf(" Erro semantico: Incompatibilidade de tipos na atribuicao. Linha: %d.\n", nlinhas);
					exit(0);
				}
			}
		}
 	}
	| TK_VLR_LITERAL{strcpy(imprimir, yytext);} 
	| CMD_LEIA;

// OBS: TROCAR EXPRESSAO POR ARV_EXPRESSAO (Acima)
ARV_EXPRESSAO: {pilha_constroi(pilha_infix);} EXPRESSAOZAO {
	if (flag_ehComparacao == 1){
	
		//teste F2 comparativo
		op_arv_comp[0] = op_comp;
		op_arv_comp[1] = '\0';
		arvore_comp = cria_arvore("comp", op_arv_comp);
		set_f1(arvore_comp, arvore_exp);
		set_f2(arvore_comp, arvore_exp2);	
	}

} ;

AVALIA_EXPRESSAO: 
	{
		pilha_constroi(pilha_posfix);
		pilha_infix = pilha_inverte(pilha_infix);
		pilha_posfix = pilha_posfixar(pilha_infix);  
		arvore_exp = arvore_monta_exp(pilha_posfix);

		if(TIPO_TERMO == 0){
			avaliado = avaliaExpressaoInt(arvore_exp, tabela_hash_var, ESCOPO_VAR);
		}
		else if(TIPO_TERMO == 1){
			avaliado = avaliaExpressaoFloat(arvore_exp, tabela_hash_var, ESCOPO_VAR);
		}
		else /* eh bool */{
			avaliado = avaliaExpressaoInt(arvore_exp, tabela_hash_var, ESCOPO_VAR);
		}
	}
;

AVALIA_EXPRESSAO2: 
	{
		pilha_constroi(pilha_posfix); 
		pilha_infix = pilha_inverte(pilha_infix);
		pilha_posfix = pilha_posfixar(pilha_infix);  
		arvore_exp2 = arvore_monta_exp(pilha_posfix);

		if(TIPO_TERMO == 0){
			avaliado2 = avaliaExpressaoInt(arvore_exp2, tabela_hash_var, ESCOPO_VAR);
		}
		else if(TIPO_TERMO == 1){
			avaliado2 = avaliaExpressaoFloat(arvore_exp2, tabela_hash_var, ESCOPO_VAR);
		}
		else /* eh bool */{
			avaliado2 = avaliaExpressaoInt(arvore_exp2, tabela_hash_var, ESCOPO_VAR);
		}
	}
	;

EXPRESSAOZAO: RESETA_PILHAS EXPRESSA1 ; 

EXPRESSA1: 
	  EXPRESSAO AVALIA_EXPRESSAO OP_COMPARATIVO EXPRESSAO AVALIA_EXPRESSAO2
	| EXPRESSAO AVALIA_EXPRESSAO;

RESETA_PILHAS: {/*verificar com as 2 pilhas*/ pilha_destroi(pilha_termo); pilha_constroi(pilha_termo); pilha_destroi(pilha_op); pilha_constroi(pilha_op);  }

EXPRESSAO:
	  EXPRESSAO token_pot {TIPO_OP = 0; pilha_putIn(pilha_infix, '^');} VERIFICACAO_OP EXPR
	| EXPR ;

EXPR:
	  EXPR token_mult {TIPO_OP = 0; pilha_putIn(pilha_infix, '*');} VERIFICACAO_OP FATOR  
	| EXPR token_div  {TIPO_OP = 0; pilha_putIn(pilha_infix, '/');} VERIFICACAO_OP FATOR	
	| EXPR token_mod  {TIPO_OP = 0; pilha_putIn(pilha_infix, '%');} VERIFICACAO_OP FATOR
	| EXPR token_and  {TIPO_OP = 1; pilha_putIn(pilha_infix, '&');} VERIFICACAO_OP FATOR
	| FATOR ;


VERIFICACAO_OP: {
	pilha_insere(pilha_op, TIPO_OP);
	if (!pilha_verifica_compatibilidade(pilha_op)) {
		printf(" Erro semantico na linha %d. Incompatibilidade de operadores na expressao.\n", nlinhas);
		exit(0);
	}
};

FATOR:
	  FATOR token_mais  {TIPO_OP = 0; pilha_putIn(pilha_infix, '+');} VERIFICACAO_OP TERMO 	
	| FATOR token_menos {TIPO_OP = 0; pilha_putIn(pilha_infix, '-');} VERIFICACAO_OP TERMO 	
	| FATOR token_or {TIPO_OP = 1; pilha_putIn(pilha_infix, '|');} VERIFICACAO_OP TERMO		
	| TERMO VERIFICACAO_TERMOS;

TERMO: 
	 OP_INCR
   | TK_VLR_NUM 
   | token_abreParen {pilha_putIn(pilha_infix, '(');} EXPRESSAO {pilha_putIn(pilha_infix, ')');} token_fechaParen
   | TK_IDENT { doge_var(tabela_hash_var, var, ident, ESCOPO_VAR); }
   | TK_VLR_BOOL
   | MULTIPLOS_NOT token_abreParen {pilha_putIn(pilha_infix, '(');} EXPRESSAO {pilha_putIn(pilha_infix, ')');} token_fechaParen
   | CHAMADA_FUNCAO 
   {
		flag_valorEhFuncao = 1; 
		if (busca(tabela_hash_func, nome_func, ESCOPO_VAR) != NULL){
			TIPO_TERMO = get_retorno(busca(tabela_hash_func, nome_func, ESCOPO_VAR));
		}
		else {
			printf(" Erro semantico: Funcao %s nao declarada. Linha: %d\n", nome_func, nlinhas);
			exit(0);
		}
   }
   ;

VERIFICACAO_TERMOS:{
	pilha_insere(pilha_termo, TIPO_TERMO);
	if (flag_eh_arg == 0){ //Se nao for argumento, insere na pilha para comparar com a atribuicao
		if(!pilha_verifica_compatibilidade(pilha_termo)) {
				printf(" Erro semantico: Incompatibilidade de tipos na expressao. Linha: %d\n", nlinhas);
				exit(0);
		}
	}
};

TK_IDENT: 
	  token_ident PILHA_IDENT 
	| token_ident PILHA_IDENT TAM_MATRIZ {
	//fazer alguma coisa
	var = busca(tabela_hash_var, nome_var, ESCOPO_VAR);
	if (var == NULL){
		printf(" Erro semantico: Variavel %s nao declarada. Linha: %d.\n", nome_var, nlinhas);
		exit(0);
	}
	else {
		if (DIM_M >= 1){
			if (DIM_N >= 1){
				if (DIM_M > get_m(var) || DIM_N > get_n(var)){
					printf(" Erro semantico: Acessando posicao inexistente em matriz. Linha: %d.\n", nlinhas);
					exit(0);
				}
			}
			else
				if (DIM_M > get_m(var)){
					printf(" Erro semantico: Acessando posicao inexistente em vetor. Linha: %d.\n", nlinhas);
					exit(0);
				}
		}
	}
} ; 

PILHA_IDENT: { 
	strcpy(nome_var, ident);
	if (busca(tabela_hash_var,nome_var,ESCOPO_VAR) != NULL){
		TIPO_VAR = get_tipo(busca(tabela_hash_var,nome_var,ESCOPO_VAR));
		TIPO_TERMO = TIPO_VAR;
		//Para colocar como argumento da funcao maximo, minimo ou central
		if (cont_arg >= 0){
			if (TIPO_TERMO == 0){
				//arg[cont_arg] = get_valor_int(busca(tabela_hash_var, nome_var, ESCOPO_VAR));
				strcpy(args, nome_var);
			}
			else if (TIPO_TERMO == 1) {
				//arg[cont_arg] = get_valor_float(busca(tabela_hash_var, nome_var, ESCOPO_VAR));
				strcpy(args, nome_var);
			}
		}
	}
	else {
		printf(" Erro semantico: Variavel %s nao declarada. Linha: %d.\n", nome_var, nlinhas);
		exit(0);
	}
	if (TIPO_TERMO == 2){
		if (strcmp(get_valor_string(busca(tabela_hash_var, nome_var, ESCOPO_VAR)), "falso") == 0){
			pilha_putVar(pilha_infix, nome_var);
		}
		else {
			pilha_putVar(pilha_infix, nome_var);
		}
	}
	else if(TIPO_TERMO == 0){
		pilha_putVar(pilha_infix, nome_var);
	}
	else {
		pilha_putVar(pilha_infix, nome_var);
	}
	flag_gambiarraAtrib++;
};

TAM_MATRIZ: 
	  token_colchete_abre token_vlr_inteiro SALVAR_M token_colchete_fecha token_colchete_abre token_vlr_inteiro SALVAR_N token_colchete_fecha // MATRIZ 
	| token_colchete_abre token_vlr_inteiro SALVAR_M token_colchete_fecha ;  // VETOR

TK_VLR_LITERAL: 
	 token_vlr_char {
	 	//insere_variavel_hash_string(tabela_hash_var, lista_atrib, yytext);
	 	
	 	arvore_teste = inicializa_arvore();
	 	arvore_teste = cria_arvore("cmd", "atrib");
		arvore_teste = insere_arvore_arvore(arvore_teste, insere_lista_arvore(lista_atrib)); //insere F1
		arvore_string = cria_arvore("string", yytext);
		arvore_teste = insere_arvore_arvore(arvore_teste, arvore_string); //Insere F2
		
		arvore_string = inicializa_arvore();
		libera(lista_atrib);
	 	lista_atrib = inicializa();
	 } 
   | token_vlr_string {
   		//insere_variavel_hash_string(tabela_hash_var, lista_atrib, yytext);
	 	
	 	arvore_teste = inicializa_arvore();
	 	arvore_teste = cria_arvore("cmd", "atrib");
		arvore_teste = insere_arvore_arvore(arvore_teste, insere_lista_arvore(lista_atrib)); //insere F1
		arvore_string = cria_arvore("string", yytext);
		
		arvore_teste = insere_arvore_arvore(arvore_teste, arvore_string); //Insere F2
		
		arvore_string = inicializa_arvore();
		arvore_teste = inicializa_arvore();
		libera(lista_atrib);
	 	lista_atrib = inicializa(); 
   	} 
   ;

CMD_LEIA:  token_read token_abreParen token_fechaParen {
	printf("LEU\n");
	leia();
	//char wow[20];
	//fflush(stdin);
	//scanf(" %s", &wow);
	//getchar();
	//arvore_teste = cria_arvore("funcao","imprima");
	//arvore_arg1 = cria_arvore("num", nome_var);
	//set_f1(arvore_teste, arvore_arg1);
	//executa_leia(arvore_teste, tabela_hash_var);
	// char str1[20], str2[30];

	// printf("Enter name: ");arvore_e
	// scanf("%s", &str1);

	// printf("Enter your website name: ");
	// scanf("%s", &str2);

	// printf("Entered Name: %s\n", str1);
	// printf("Entered Website:%s", str2);

	// printf("DEVERIA ESCANEAR\n");
	if (get_tipo(busca(tabela_hash_var, nome_var, ESCOPO_VAR)) == 0){
	}
} ;

TK_VLR_NUM: 
	  token_vlr_inteiro { TIPO_TERMO = 0; pilha_insere(pilha_infix, atoi(vlr_int)); }
	| token_vlr_real    { TIPO_TERMO = 1; pilha_insert(pilha_infix, atof(vlr_real)); }
	| token_menos token_vlr_inteiro { TIPO_TERMO = 0; pilha_insere(pilha_infix, -1*atoi(vlr_int)); }
	| token_menos token_vlr_real    { TIPO_TERMO = 1; pilha_insert(pilha_infix, -1*atof(vlr_real));} ;


MULTIPLOS_NOT:
	  MULTIPLOS_NOT token_not { pilha_putIn(pilha_infix, '!'); }
	| token_not { pilha_putIn(pilha_infix, '!'); };

TK_VLR_BOOL: 
	  MULTIPLOS_NOT token_true { pilha_insere(pilha_infix, 1); TIPO_TERMO = 2; }
    | MULTIPLOS_NOT token_false { pilha_insere(pilha_infix, 0); TIPO_TERMO = 2; }
    | token_true { pilha_insere(pilha_infix, 1); TIPO_TERMO = 2;}
    | token_false { pilha_insere(pilha_infix, 0); TIPO_TERMO = 2;}
    | MULTIPLOS_NOT TK_IDENT { doge_var(tabela_hash_var, var, ident, ESCOPO_VAR); };

OP_INCR: TK_IDENT { doge_var(tabela_hash_var, var, ident, ESCOPO_VAR); } token_increment
       | TK_IDENT { doge_var(tabela_hash_var, var, ident, ESCOPO_VAR); } token_decrement
       ;

OP_COMPARATIVO: OPERADORES_COMPARATIVOS 
	{
		flag_ehComparacao = 1;
	}	
;

OPERADORES_COMPARATIVOS:
	  token_maior {op_comp = '>';}// aceitar exp de numeros
	| token_maior_igual {op_comp = 'G';}// aceitar exp de numeros
	| token_menor {op_comp = '<';} // aceitar exp de numeros
	| token_menor_igual {op_comp = 'L';} // aceitar exp de numeros
	| token_igual {op_comp = '=';} //aceitar exp de tudo
	| token_diferente {op_comp = 'D';} //aceitar exp de tudo
	;

%%

#include "lex.yy.c"

int main(void){

	lista_var = inicializa();
	lista_atrib = inicializa();
	var = inicializa();
	lista_func = inicializa();
	func = inicializa();
	tabela_hash_var = inicializa_hash();
	tabela_hash_func = inicializa_hash();
	pilha_termo = pilha_constroi(pilha_termo);
	pilha_op = pilha_constroi(pilha_op);
	pilha_infix = pilha_constroi(pilha_infix);
	arvore_exp = inicializa_arvore();
	arvore_exp2 = inicializa_arvore();
	arvore_comp = inicializa_arvore();
	arvore_teste = inicializa_arvore();
	arvore_final = inicializa_arvore();
	arvore_string = inicializa_arvore();
	/*
	char menuSelection;
	printf("\n ----- Menu G-Portugol -----\n");
	printf(" (1) Compilar Programa\n");
	printf(" (2) Executar Programa\n");
	printf(" (3) Listar programas no diretorio Exemplos\n");
	printf(" (4) Listar programas compilados\n");
	printf(" (5) Imprimir Arvore de Execucao\n");
	printf(" (6) Executar programa e imprimir tabela de variaveis\n");
	printf(" (7) Sair\n");
	printf(" ----------------------------\n\n");

	scanf("%c", &menuSelection);

	while(1){
		switch (menuSelection){
			case '1':
				printf(" Compilando o programa.\n");
				yyparse();
				printf(" Programa compilado.\n");
				break;
			case '2':
				printf(" Executando o programa.\n");
				// executa_arvore_final(arvore_final, tabela_hash_var);
				printf(" Programa executado.\n");
				break;
			case '3':
				printf(" Programas no diretorio Exemplos:\n");
				// n sei mexer com arq, mas deve ter um for no meio
				break;
			case '4':
				printf(" Programas compilados:\n");
				// n sei mexer com arq
				break;
			case '5':
				printf(" Arvore de execucao do programa:\n");
				arvore_imprime_final(arvore_final);
				break;
			case '6':
				printf(" Tabela de variaveis do programa:\n");
				imprime_hash(tabela_hash_var);
				break;
			case '7':
				exit(0);
			default:
				printf("Opcao invalida.");
		}
	}
	*/
	//leia();
	yyparse();

	verifica_variavel_usada(tabela_hash_var);
	//imprime_hash(tabela_hash_var);
	printf("ARVORE FINAL\n");
	
	//arvore_imprime_final(arvore_final);
	// arvore_imprime(arvore_final);
	printf("EXECUTA\n");
	executa_arvore_final(arvore_final, tabela_hash_var);
	imprime_hash(tabela_hash_var);
	return 0;
}

yyerror(void){
  printf(" Erro sintatico. Linha: %d\n", nlinhas);
  exit(1);
}
