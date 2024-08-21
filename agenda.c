#include "listaestatica.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <locale.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

//"LOGO" DA AGENDA  E MENU ARMAZENADA EM UMA FUNÇÃO
void exibirMenu() {
    setlocale(LC_ALL, "Portuguese");

    printf("\n\t\t\t\t\t+-----------------------------+\n");
    printf("\n\t\t\t\t\t¦          \033[1;34mA G E N D A\033[0m        ¦\n");
    printf("\n\t\t\t\t\t+-----------------------------+\n");
    printf("\n\t\t\t\t\t+-----------------------------+\n");
    printf("\n\t\t\t\t\t¦ \033[1;32m[1]\033[0m \033[1;37mADICIONAR NOVO CONTATO\033[0m  ¦\n");
    printf("\n\t\t\t\t\t¦ \033[1;32m[2]\033[0m \033[1;37mDELETAR CONTATO\033[0m         ¦\n");
    printf("\n\t\t\t\t\t¦ \033[1;32m[3]\033[0m \033[1;37mPESQUISAR CONTATO\033[0m       ¦\n");
    printf("\n\t\t\t\t\t¦ \033[1;32m[4]\033[0m \033[1;37mTODOS CONTATOS NA AGENDA\033[0m¦\n");
    printf("\n\t\t\t\t\t¦ \033[1;31m[0]\033[0m \033[1;37mSAIR\033[0m                    ¦\n");
    printf("\n\t\t\t\t\t+-----------------------------+\n");
    printf("\n\t\t\t\t\tSELECIONE A OPÇÃO DESEJADA ;) : ");
}

//FUNCAO ABRIR LISTA
void abrirLista(EstaticList *list) {
    list->tamanho = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

//INICIO DAS FUNCIONALIDADES DA AGENDA
//FUNCAO CADASTRAR/CREATE CONTATO NA AGENDA
int cadastrarCTT(EstaticList *list, ctt contato) {
    if (list->tamanho >= MAX_CONTATOS) {
        printf("Não é possível o cadastro de mais contatos. Você atingiu o limite de contatos.\n");
        return 0;
    }
    list->contatos[list->tamanho] = contato;
    list->tamanho++;
    
    FILE *arquivo = fopen("contatos.txt", "a"); // arquivo de texto = txt
    if (arquivo == NULL) {
        perror("Erro na abertura do arquivo");
        exit(EXIT_FAILURE);
    }
    fprintf(arquivo, "name: %s\naddresAcount: %s\nnumber: %s\n\n", contato.name, contato.addresAcount, contato.number);
    fclose(arquivo);

    printf("Contato cadastrado na agenda.\n");
    return 1;
}

//FUNCAO DE REMOVER CONTATO DA AGENDA
int deleteCTT(EstaticList *list, char *name) {
    int i, j, encontrado = 0;

    for (i = 0; i < list->tamanho; i++) {
        if (strcmp(list->contatos[i].name, name) == 0) {
            encontrado = 1;
            break;
        }
    }

    if (encontrado) {
        for (j = i; j < list->tamanho - 1; j++) {
            list->contatos[j] = list->contatos[j + 1];
        }
        list->tamanho--;

        FILE *arquivo = fopen("contatos.txt", "r");
        FILE *temp = fopen("temp.txt", "w");
        if (arquivo == NULL || temp == NULL) {
            perror("Erro ao abrir o arquivo");
            exit(EXIT_FAILURE);
        }

        char linha[256];
        while (fgets(linha, sizeof(linha), arquivo)) {
            if (strstr(linha, name) == NULL) {
                fputs(linha, temp);
            } else {
                fgets(linha, sizeof(linha), arquivo);
                fgets(linha, sizeof(linha), arquivo);
            }
        }

        fclose(arquivo);
        fclose(temp);

        remove("contatos.txt");
        rename("temp.txt", "contatos.txt");

        printf("Contato removido com sucesso!\n");
        return 1;
    } else {
        printf("Contato não encontrado.\n");
        return 0;
    }
}

ctt* pesquisarCTT(EstaticList *list, char *name) {
	int i;
	int encontrado = 0;
    for ( i = 0; i < list->tamanho; i++) {
        if (strcmp(list->contatos[i].name, name) == 0) {
            return &list->contatos[i];
        }
    }
    return NULL;
}

//FUNCAO PARA ADICIONAR CONDIÇÃO DE LISTAGEM --> ORDEM ALFABÉTICA
void OrdemDeListagem(EstaticList *list) {
    ctt temp;
    int i, j;
    int encontrado = 0;
    for ( i = 0; i < list->tamanho - 1; i++) {
        for ( j = i + 1; j < list->tamanho; j++) {
            if (strcmp(list->contatos[i].name, list->contatos[j].name) > 0) {
                temp = list->contatos[i];
                list->contatos[i] = list->contatos[j];
                list->contatos[j] = temp;
            }
        }
    }
}

//FUNCAO LISTAGEM DE CONTATOS CADASTRADOS NA AGENDA
void listarCTT(EstaticList *list) {
    if (list->tamanho == 0) {
        printf("Não há contatos na agenda.\n");
        return;
    }

    OrdemDeListagem(list);
    int i;
    int encontrado = 0;
    for ( i = 0; i < list->tamanho; i++) {
        printf("name: %s\nEmail: %s\nTelefone: %s\n\n", list->contatos[i].name, list->contatos[i].addresAcount, list->contatos[i].number);
    }
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

//FUNCAO PARA ABRIR MENU DE CADASTRO; PARA REMOÇÃO DE CONTATO; LISTAGEM DE CONTATO;
void abrirMenu(EstaticList *agenda) {
    int opcao;
    char name[50];
    ctt contato;
    ctt *buscado;

    do {
        system("cls");
        exibirMenu();
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                printf("Nome: ");
                fgets(contato.name, sizeof(contato.name), stdin);
                contato.name[strcspn(contato.name, "\n")] = '\0';

                printf("Email: ");
                fgets(contato.addresAcount, sizeof(contato.addresAcount), stdin);
                contato.addresAcount[strcspn(contato.addresAcount, "\n")] = '\0';

                printf("Telefone: ");
                fgets(contato.number, sizeof(contato.number), stdin);
                contato.number[strcspn(contato.number, "\n")] = '\0';

                cadastrarCTT(agenda, contato);
                break;
//PARA REMOÇÃO DE CADASTRADO NA AGENDA PELO SEU NOME ANTES CADASTRADO
            case 2:
                printf("Nome do contato a remover: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';

                deleteCTT(agenda, name);
                break;
//PARA PESQUISAR CONTATO NA AGENDA PELO SEU NOME ANTES CADASTRADO
            case 3:
                printf("Nome do contato a buscar: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';

                buscado = pesquisarCTT(agenda, name);
                if (buscado) {
                    printf("Contato encontrado!:\nNome do contato: %s\nEmail do contato: %s\nTelefone: %s\n", buscado->name, buscado->addresAcount, buscado->number);
                } else {
                    printf("Contato não cadastrado na agenda! Cadastre...\n");
                }
                break;
            case 4:
                listarCTT(agenda);
                break;
            case 0:
                printf("Encerrando a agenda...\n");
                exit(0);
            default:
                printf("\nSelecione uma opção da agenda! Insira novamente.\n");
                break;
        }

        printf("Pressione qualquer tecla para continuar...");
        getchar();

    } while (opcao != 0);
}
