#define MAX_CONTATOS 100
#ifndef LISTAESTATICA_H
#define LISTAESTATICA_H
//BIBLIOTECA

typedef struct {
	    char addresAcount[100]; //email
	    char number[30];//telefone
    	char name[75];//nome
} ctt; //referencial da struct
//struct -> contato

typedef struct {
    ctt contatos[MAX_CONTATOS];
    int tamanho;
} EstaticList;
//LISTA ESTATICA

//FUNCOES DA AGENDA
void abrirLista(EstaticList *list);//open list 
int cadastrarCTT(EstaticList *list, ctt contato); //create
int deleteCTT(EstaticList *list, char *name);//delete
ctt* pesquisarCTT(EstaticList *list, char *name);//search
void listarCTT(EstaticList *list)//read
void OrdemDeListagem(EstaticList *list);//inserir parâmetro de listagem
#endif
