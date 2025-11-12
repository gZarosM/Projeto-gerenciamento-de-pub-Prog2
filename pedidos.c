#include "funcoes.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Bebida bebidas[MAX_BEBIDAS];
Comida comidas[MAX_COMIDAS];

void cadastroPedido(Bebida bebidas[], int max_bebidas, Comida comidas[], int max_comidas)
{
   FILE *arq = escreverFinalArquivo(3);
   FILE *consultaBebida, *consultaComidas, *totalPedidos;
   int op = 1, codigoItem, quantidadeItem, id;
   float valorTotalItem, valorTotalBebida, valorTotalComida;
   char escolha = 'S', escolhaBebida, escolhaComida;
   char c;

   
   while (escolha =='S')
   {
      while ((c = getchar()) != '\n' && c != EOF) ;

      id = lerID();
      id++;
      novoID(id);

      valorTotalItem = 0;
      valorTotalBebida = 0;
      valorTotalComida = 0;

      consultaBebida = fopen("baseDados.txt", "r");
      consultaComidas = fopen("comidas.txt","r");

      printf("ID do pedido: %d\n", id);

      int count = 0;

      printf("O cliente consumiu alguma bebida? (S/N)\n");
      scanf(" %c", &escolhaBebida);
      converteMaiuscula(&escolhaBebida);

      if(escolhaBebida == 'S'){
         while (fscanf(consultaBebida, "%d,%49[^,],%f,%49[^,],%49[^,],%d",
               &bebidas[count].status,
               bebidas[count].nome,
               &bebidas[count].preco,
               bebidas[count].tipo,
               bebidas[count].marca,
               &bebidas[count].quantidadeGarrafas) == 6){
               if(bebidas[count].status == 1)
                  printf("(%d)%s\tR$%.2f\n", count, bebidas[count].nome, bebidas[count].preco);
                     
               count++;
               if(count >= max_bebidas)break;
            }

         do{      
               printf("Insira o codigo da bebida consumida: \n");
               scanf("%d", &codigoItem);
               printf("Quantidade: ");
               scanf("%d", &quantidadeItem);

               valorTotalItem = bebidas[codigoItem].preco * quantidadeItem;
      
               valorTotalBebida += valorTotalItem;

               fprintf(arq, "%d,%s,%d,%.2f\n", id, bebidas[codigoItem].nome, quantidadeItem, valorTotalItem);
               printf("Deseja inserir outra bebida? (1 - Sim, 0 - Nao)");
               scanf("%d", &op);
            }while(op != 0);
         }
          

      op = 1;
      count = 0;
      valorTotalItem = 0;


      printf("O cliente consumiu algum alimento? (S/N)\n");
      scanf(" %c", &escolhaComida);

      converteMaiuscula(&escolhaComida);

      if(escolhaComida == 'S'){
         printf("LISTAGEM ALIMENTOS:\n");

               while (fscanf(consultaComidas, " %49[^,],%f,%49[^,],%d",
                  comidas[count].nome,
                  &comidas[count].preco,
                  comidas[count].descricao,
                  &comidas[count].status) == 4){
                  if(comidas[count].status == 1)
                        printf("(%d)%s\tR$%.2f\n", count, comidas[count].nome, comidas[count].preco);            

                  count++;  
                  if(count >= max_comidas)
                     break;
               }
         do{
            printf("Insira o codigo do alimento consumido: \n");
            scanf("%d", &codigoItem);
            printf("Quantidade: ");
            scanf("%d", &quantidadeItem);

            valorTotalItem = comidas[codigoItem].preco * quantidadeItem;
      
            valorTotalComida += valorTotalItem;

            fprintf(arq, "%d,%s,%d,%.2f\n", id, comidas[codigoItem].nome, quantidadeItem, valorTotalItem);
            printf("Deseja inserir outro alimento? (1 - Sim, 0 - Nao)");
            scanf("%d", &op);       
         }while(op != 0);
   
      }

      printf("\n");

      printf("Deseja cadastrar mais algum pedido(S/N)?\n");
      scanf(" %c", &escolha);
      escolha = toupper((unsigned char)escolha);

      printf("\nValor total do Pedido: -------- R$%.2f\n", valorTotalBebida+valorTotalComida);
      
      totalPedidos = fopen("totalPedidos.txt", "a");
      fprintf(totalPedidos, "%d,%.2f\n", id, valorTotalBebida+valorTotalComida);

      fclose(totalPedidos);
      fclose(consultaBebida);
      fclose(consultaComidas);
   }
   
   fclose(arq);

}

int menuPedido()
{
      cadastroPedido(bebidas, MAX_BEBIDAS, comidas, MAX_COMIDAS);
      return 0;
}

