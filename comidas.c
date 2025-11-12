#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <locale.h> 
#include "funcoes.h"  
   


void cadastrarComida(){
    Comida comida; // struct
    FILE *arq = escreverFinalArquivo(2);
    if (arq == NULL){
        printf("Erro ao abrir arquivo para leitura.\n");
        return;
    }

    char escolha = 'S';
    char c;

    while (escolha == 'S'){
        // Limpeza de buffer (se houver lixo do loop anterior ou do menu)
        while ((c = getchar()) != '\n' && c != EOF);

        printf("Nome da comida: ");
        fgets(comida.nome, sizeof(comida.nome), stdin);
        comida.nome[strcspn(comida.nome, "\n")] = '\0'; // Remove o \n do final

        printf("\n");

        printf("Preço: ");
        scanf("%f", &comida.preco);

        // Limpa o buffer após o scanf
        while ((c = getchar()) != '\n' && c != EOF);

        printf("\n");

        printf("Descrição da comida: ");
        fgets(comida.descricao, sizeof(comida.descricao), stdin);
        comida.descricao[strcspn(comida.descricao, "\n")] = '\0';

        printf("\n");

        char *campoComidas[] = {comida.nome, comida.descricao, NULL};
        converterCampos(campoComidas);

        comida.status = 1; // 1 significa que a estrutura está ativa

        // Escrita no arquivo
        fprintf(arq, "%s,%.2f,%s,%d\n", comida.nome, comida.preco, comida.descricao, comida.status);

        printf("\n");

        printf("Deseja cadastrar mais alguma comida (S/N) ? ");
        scanf(" %c", &escolha);
        escolha = toupper((unsigned char)escolha);
        printf("\n");
    }
    fclose(arq);
}

// Função para carregar as comidas do arquivo para um array
int carregarComidas(Comida comidas[], int max_comidas){
    FILE *arq = lerArquivo(2);
    if (arq == NULL){
        printf("Erro ao abrir arquivo para leitura.\n");
        return 0;
    }

    int count = 0;
    while (fscanf(arq, "%49[^,],%f,%49[^,],%d\n",
                  comidas[count].nome,
                  &comidas[count].preco,
                  comidas[count].descricao,
                  &comidas[count].status) == 4){
        count++;
        if (count >= max_comidas)
            break;
    }

    fclose(arq);
    return count;
}

// Função para salvar todas as comidas de volta no arquivo
void salvarComidas(Comida comidas[], int num_comidas){
    FILE *arq = reescreverArquivo(2);
    if (arq == NULL){
        printf("Erro     ao abrir arquivo para escrita.\n");
        return;
    }

    for (int i = 0; i < num_comidas; i++){
        fprintf(arq, "%s,%.2f,%s,%d\n",
                comidas[i].nome,
                comidas[i].preco,
                comidas[i].descricao,
                comidas[i].status);
    }

    fclose(arq);
}

//listar comidas
void listarComidas() {
    Comida comidas[MAX_COMIDAS];
    int num_comidas = carregarComidas(comidas, MAX_COMIDAS);

    if (num_comidas == 0) {
        printf("\nNenhuma comida cadastrada no momento.\n");
        return;
    }

    int opcao;
    printf("\n===== MENU DE LISTAGEM =====\n");
    printf("1. Mostrar TODAS as comidas\n");
    printf("2. Mostrar apenas ATIVAS\n");
    printf("3. Mostrar apenas INATIVAS\n");
    printf("============================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    printf("\n===== LISTA DE COMIDAS =====\n");

    int exibiu = 0;
    for (int i = 0; i < num_comidas; i++) {
        int mostrar = 0;

        switch (opcao) {
            case 1: // todas
                mostrar = 1;
                break;
            case 2: // apenas ativas
                if (comidas[i].status == 1) mostrar = 1;
                break;
            case 3: // apenas inativas
                if (comidas[i].status == 0) mostrar = 1;
                break;
            default:
                printf("\nOpção inválida!\n");
                return;
        }

        if (mostrar) {
            exibiu = 1;
            printf("\n-------------------------------\n");
            printf("Nome: %s\n", comidas[i].nome);
            printf("Preco: R$ %.2f\n", comidas[i].preco);
            printf("Descricao: %s\n", comidas[i].descricao);
            printf("Status: %s\n", comidas[i].status == 1 ? "ATIVO" : "INATIVO");
        }
    }

    if (!exibiu)
        printf("\nNenhuma comida encontrada para o filtro escolhido.\n");

    printf("\n===============================\n");
}

//Inativando comida
void inativarComida() {
    Comida comidas[MAX_COMIDAS];
    int num_comidas = carregarComidas(comidas, MAX_COMIDAS);

    if (num_comidas == 0) {
        printf("Nenhuma comida encontrada no arquivo.\n");
        return;
    }

    char nomeBusca[MAX_STRING];
    char escolha = 'S';
    char c;

    while (toupper(escolha) == 'S') {
        // Limpa buffer antes de ler o nome
        while ((c = getchar()) != '\n' && c != EOF);

        printf("\nDigite o nome da comida que deseja inutilizar: ");
        fgets(nomeBusca, sizeof(nomeBusca), stdin);
        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

        // Converte para maiúsculas
        for (size_t i = 0; i < strlen(nomeBusca); i++)
            nomeBusca[i] = toupper((unsigned char)nomeBusca[i]);

        int encontrado = 0;

        for (int i = 0; i < num_comidas; i++) {
            if (strcmp(comidas[i].nome, nomeBusca) == 0) {
                encontrado = 1;
                if (comidas[i].status == 0) {
                    printf("\n A comida '%s' já está inativada.\n", comidas[i].nome);
                } else {
                    comidas[i].status = 0;
                    printf("\n Comida '%s' inativada com sucesso!\n", comidas[i].nome);
                }
                break;
            }
        }

        if (!encontrado) {
            printf("\n Comida não encontrada. Tente novamente.\n");
        }

        printf("\nDeseja inativar outra comida? (S/N): ");
        scanf(" %c", &escolha);
        escolha = toupper((unsigned char)escolha);
    }

    salvarComidas(comidas, num_comidas);
    printf("\nAlterações salvas no arquivo com sucesso!\n\n");
}

//Ativando comida
void ativarComida() {
    Comida comidas[MAX_COMIDAS];
    int num_comidas = carregarComidas(comidas, MAX_COMIDAS);

    if (num_comidas == 0) {
        printf("Nenhuma comida encontrada no arquivo.\n");
        return;
    }

    char nomeBusca[MAX_STRING];
    char escolha = 'S';
    char c;

    while (toupper(escolha) == 'S') {
        // Limpa buffer antes de ler o nome
        while ((c = getchar()) != '\n' && c != EOF);

        printf("\nDigite o nome da comida que deseja ativar: ");
        fgets(nomeBusca, sizeof(nomeBusca), stdin);
        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

        // Converte para maiúsculas
        for (size_t i = 0; i < strlen(nomeBusca); i++)
            nomeBusca[i] = toupper((unsigned char)nomeBusca[i]);

        int encontrado = 0;

        for (int i = 0; i < num_comidas; i++) {
            if (strcmp(comidas[i].nome, nomeBusca) == 0) {
                encontrado = 1;
                if (comidas[i].status == 1) {
                    printf("\n A comida '%s' já está ativada.\n", comidas[i].nome);
                } else {
                    comidas[i].status = 1;
                    printf("\n Comida '%s' ativada com sucesso!\n", comidas[i].nome);
                }
                break;
            }
        }

        if (!encontrado) {
            printf("\n Comida não encontrada. Tente novamente.\n");
        }

        printf("\nDeseja ativar outra comida? (S/N): ");
        scanf(" %c", &escolha);
        escolha = toupper((unsigned char)escolha);
    }

    salvarComidas(comidas, num_comidas);
    printf("\nAlterações salvas no arquivo com sucesso!\n\n");
}

// Função de atualização completa da comida
void atualizarComida(){

    Comida comidas[MAX_COMIDAS];
    int num_comidas = carregarComidas(comidas, MAX_COMIDAS); // ANTES DE ATUALIZAR TERÁ QUE SALVAR TUDO QUE CONTINHA NO ARQUIVO

    if (num_comidas == 0){
        printf("Nenhuma comida encontrada no arquivo.\n");
        return;
    }

    char nomeBusca[MAX_STRING];
    char c;

    // Limpa buffer
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Digite o nome da comida que deseja atualizar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    // Converte para maiúsculas
    converteMaiuscula(nomeBusca);

    int encontrado = 0;

    for (int i = 0; i < num_comidas; i++){
        if (strcmp(comidas[i].nome, nomeBusca) == 0){
            encontrado = 1;
            printf("\n--- Atualizando %s ---\n", comidas[i].nome);

            char opcao;

            // TROCA O NOME
            printf("Deseja alterar o NOME? (S/N): ");
            scanf(" %c", &opcao);
            opcao = toupper(opcao);
            while ((c = getchar()) != '\n' && c != EOF);    // limpa buffer
            if (opcao == 'S'){
                printf("Novo nome: ");
                fgets(comidas[i].nome, sizeof(comidas[i].nome), stdin);
                comidas[i].nome[strcspn(comidas[i].nome, "\n")] = '\0';
                for (size_t j = 0; j < strlen(comidas[i].nome); j++)
                    comidas[i].nome[j] = toupper((unsigned char)comidas[i].nome[j]);
            }

            // TROCAR O PREÇO
            printf("Deseja alterar o PREÇO? (S/N): ");
            scanf(" %c", &opcao);
            opcao = toupper(opcao);
            if (opcao == 'S'){
                printf("Novo preço: ");
                scanf("%f", &comidas[i].preco);
            }
            while ((c = getchar()) != '\n' && c != EOF);    // limpa buffer

            // TROCAR A DESCRIÇÃO
            printf("Deseja alterar a DESCRIÇÃO? (S/N): ");
            scanf(" %c", &opcao);
            opcao = toupper(opcao);
            while ((c = getchar()) != '\n' && c != EOF);    // limpa buffer
            if (opcao == 'S'){
                printf("Novo tipo: ");
                fgets(comidas[i].descricao, sizeof(comidas[i].descricao), stdin);
                comidas[i].descricao[strcspn(comidas[i].descricao, "\n")] = '\0';
                for (size_t j = 0; j < strlen(comidas[i].descricao); j++)                       // converte para maiusculo
                    comidas[i].descricao[j] = toupper((unsigned char)comidas[i].descricao[j]);
            }
            
            printf("\nProduto atualizado com sucesso!\n");

            salvarComidas(comidas, num_comidas);
            break;
        }
    }

    if (!encontrado)
        printf("\nComida não encontrada.\n");
}

int menuComidas(){
    int decisao;

    void(*operation[])(void) = {cadastrarComida, atualizarComida, inativarComida, ativarComida, listarComidas};

    do
    {
        printf("=== Gerencie seu PUB ===\n");
        printf("1) Cadastrar comidas\n");
        printf("2) Atualizar comida\n");
        printf("3) Inativar comida\n");
        printf("4) Ativar comida\n");
        printf("5) Listar comidas\n");
        //printf("45) CADASTROS PRONTOS\n");
        printf("0) Sair\n");
        printf("Escolha: ");
        scanf("%d", &decisao);
        printf("\n");

        if(decisao == 0){
            return 0;
            break;
        }       
        else{
            if(decisao > 5 || decisao < 0)
                printf("Opcao invalida!\n");
            else{
                operation[decisao-1]();
            }
        }

    } while (decisao != 0);
}