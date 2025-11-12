#ifndef funcoes_h
#define funcoes_h
#define MAX_STRING 50 // Tamanho máximo string
#define MAX_BEBIDAS 100 //QTD máxima de bebidas
#define MAX_COMIDAS 25
#include <ctype.h>
#include <string.h>
#include <locale.h>
#include <stdio.h>

// Especificações de bebidas
typedef struct bebidas
{
    char nome[MAX_STRING];
    float preco;
    int status;
    char tipo[MAX_STRING]; // alcoolica, refrigerante, suco e etc
    char marca[MAX_STRING];
    int quantidadeGarrafas; // essa quantidade refere-se a garrafas e não a MLS, por isso é int
} Bebida;

//Especificações de comidas
typedef struct comidas{
    char nome[50];
    float preco;
    char descricao[151];
    int status;
} Comida;
/*
//Especificação dos itens
typedef struct item{
    char nome[50];
    int quantidade;
    float precoUnitario;
}Item;

//Especificações do pedido
typedef struct pedido{
    int idPedido;
    Item itens[20];
    float valorTotalPedido;
}Pedido;*/

//comentei essas duas structs pois achava que era necessario
//mas consegui resolver a questao do pedido e relatorios sem struct

FILE *lerArquivo(int a);
FILE *escreverFinalArquivo(int a);
FILE *reescreverArquivo(int a);
void converteMaiuscula(char *string);
void converterCampos(char *ptr[]);
void imprimeRelatorio();
int menuBebidas();
int menuComidas();
int menuPedido();
int lerID();
int novoID(int id);

#endif