#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <locale.h> 
#include "funcoes.h"

Bebida bebidas[MAX_BEBIDAS];
Comida comidas[MAX_COMIDAS];


int main(){
    int op;

    while(1){
        printf("Deseja abrir qual menu: \n");
        printf("0 - Bebidas\n");
        printf("1 - Comidas\n");
        printf("2 - Pedidos\n");
        printf("3 - Gerar relatorio\n");
        printf("5 - Sair\n");
        scanf("%d", &op);

        if(op == 1)
            menuComidas();
        else{
            if (op == 0)
                menuBebidas();
            else{
                if(op == 2)
                    menuPedido();
                else{
                    if(op == 5){
                        printf("\tSaindo do sistema...");
                        break;
                    } 
                    else
                        if (op == 3)
                            imprimeRelatorio();
                        else
                            printf("Opcao Invalida\n");
                }
            }
        }   
    }
    return 0;
}
