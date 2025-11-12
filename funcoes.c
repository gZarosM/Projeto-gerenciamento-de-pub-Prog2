#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "funcoes.h"

void mensagem(){
    printf("Erro ao abrir arquivo!\n");
}

//Função que converterá uma string para letras maiusculas
void converteMaiuscula(char *string){   
    for (size_t i = 0; i < strlen(string); i++)
    {
        string[i] = toupper((unsigned char)string[i]);
    }
}
//Função receberá os campos a serem convertidos para letras maiusculas
void converterCampos(char *ptr[]){
    for (int i = 0; ptr[i] != NULL; i++){
        converteMaiuscula(ptr[i]);
    }
}

FILE *lerArquivo(int a){
    FILE *arq;

    if (a == 1){
        arq = fopen("baseDados.txt", "r");

        if (arq == NULL){
            mensagem();
            return NULL;
        }
    }
    else {
        if (a == 2){
            arq = fopen("comidas.txt", "r");
            if (arq == NULL){
                mensagem();
                return NULL;
            }
        }
        else{
            arq = fopen("pedidos.txt", "r");
            if (arq == NULL){
                mensagem();
                return NULL;
            }
        }      
    }

    return arq;
}

// Função para poder acrescentar algo no arquivo 
FILE *escreverFinalArquivo(int a){
    FILE *arq;

    if (a == 1){
        arq = fopen("baseDados.txt", "a");

        if (arq == NULL){
            mensagem();
            return NULL;
        }
    }
    else {
        if (a == 2){
            arq = fopen("comidas.txt", "a");
            if (arq == NULL){
                mensagem();
                return NULL;
            }
        }
        else{
            arq = fopen("pedidos.txt", "a");
            if (arq == NULL){
                mensagem();
                return NULL;
            }
        }
    }

    return arq;
}

// Função para poder reescrever o arquivo
FILE *reescreverArquivo(int a){
    FILE *arq;
    if (a == 1){
        arq = fopen("baseDados.txt", "w");

        if (arq == NULL){
            mensagem();
            return NULL;
        }
    }
    else {
        if (a == 2){
            arq = fopen("comidas.txt", "w");
            if (arq == NULL){
                mensagem();
                return NULL;
            }
        }
        else{
            arq = fopen("pedidos.txt", "w");
            if (arq == NULL){
                mensagem();
                return NULL;
            }
        }
    }
 
    return arq;
}

int lerID(){
    FILE *lerId = fopen("ultimoID.txt", "r");

    int id = 0;

    if(lerID != NULL){
        fscanf(lerId, "%d", &id);
        fclose(lerId);
    }

    return id;
}

int novoID(int id){
    FILE *escreverID = fopen("ultimoID.txt","w");

    if(escreverID != NULL){
        fprintf(escreverID, "%d", id);
        fclose(escreverID);
    }
}

void imprimeRelatorio(){
    FILE *arq = fopen("totalPedidos.txt", "r");
    int idPedido;
    float valor, somaTotal = 0;
    while(fscanf(arq, "%d,%f", &idPedido, &valor) != EOF){
        printf("Id Pedido: %d\tValor: %.2f\n", idPedido, valor);
        somaTotal += valor;
    }

    printf("--- Valor total dos pedidos: R$%.2f ---\n\n", somaTotal);
    fclose(arq);
}