#include "../include/animal.h"
#include "../include/utils.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int cadastrar_animal(){
    bool resultado_verificacao;
    FILE *banco_de_animais = fopen("../data/animal.txt","a+");
    resultado_verificacao= verificacao_de_arquivo(banco_de_animais);
    if (resultado_verificacao == 0){
        return 0;
    }
    animal cadastro_animal;

    int id = 1;
    char linha[200];
    rewind(banco_de_animais);
    while (fgets(linha, sizeof(linha), banco_de_animais)) {
        id++;
    }
    cadastro_animal.identificador = id;
    printf("\nentre com o Nome do animal : ");
    fgets(cadastro_animal.nome, sizeof(cadastro_animal.nome), stdin);
    cadastro_animal.nome[strcspn(cadastro_animal.nome, "\n")] = '\0';

    printf("\nentre com a Raca do animal : \n");
    printf("1 - Cachorro\n");
    printf("2 - Gato\n");
    printf("3 - Coelho\n");
    scanf("%i",&cadastro_animal.raca);
    limpar_buffer();
    do {
        printf("\nDigite a faixa etaria do animal:\n");
        printf("1 - Recem nascido (menor de 1 ano)\n");
        printf("2 - Adulto (1-10 anos)\n");
        printf("3 - Velho (acima de 10 anos)\n");
        scanf("%d", &cadastro_animal.faixa_etaria);
        limpar_buffer();
        if (cadastro_animal.faixa_etaria < 1 || cadastro_animal.faixa_etaria > 3) {
            printf("Erro: faixa etaria invalida. Tente novamente.\n");
        }
        
    } while (cadastro_animal.faixa_etaria < 1 || cadastro_animal.faixa_etaria > 3);

     do {
        printf("\nO animal esta apto para adocao? 1-Sim 0-Nao\n");
        scanf("%d", &cadastro_animal.apto_para_adocao);
        limpar_buffer();
        if (cadastro_animal.apto_para_adocao != 0 && cadastro_animal.apto_para_adocao != 1) {
            printf("\nErro: valor invalido. Tente novamente.\n");
        }
    } while (cadastro_animal.apto_para_adocao != 0 && cadastro_animal.apto_para_adocao != 1);

    fprintf(banco_de_animais, "%d;%s;%i;%d;%d\n",
            cadastro_animal.identificador,
            cadastro_animal.nome,
            cadastro_animal.raca,
            cadastro_animal.faixa_etaria,
            cadastro_animal.apto_para_adocao);

    fclose(banco_de_animais);
    return 1;
}


int deletar_animal(char *identificador_de_exclusao) {
    // criacao de 1 arquivo copia para apagar o animal
    FILE *banco_de_animais = fopen("../data/animal.txt", "r");
    FILE *banco_de_animais_temp = fopen("../data/temp.txt", "w");
    char identificador_da_linha[200];
    int encontrado = 0;

    if (banco_de_animais == NULL || banco_de_animais_temp == NULL) {
        return 0;
    }

    while (fgets(identificador_da_linha, sizeof(identificador_da_linha), banco_de_animais)) {
        char primeira_palavra[100];
        int i = 0;

        while (identificador_da_linha[i] != ';' && identificador_da_linha[i] != '\0' && identificador_da_linha[i] != '\n') {
            primeira_palavra[i] = identificador_da_linha[i];
            i++;
        }
        primeira_palavra[i] = '\0';

        if (strcmp(primeira_palavra, identificador_de_exclusao) == 0) {
            fprintf(banco_de_animais_temp, ";\n");
            encontrado = 1;
        } else {
            fputs(identificador_da_linha, banco_de_animais_temp);
        }
    }

    fclose(banco_de_animais);
    fclose(banco_de_animais_temp);

    remove("../data/animal.txt");
    rename("../data/temp.txt", "../data/animal.txt");

    return encontrado;
}


int atualizaco_de_animal(char *ponteiro_de_atualizacao){
    int atualizacao_de_atributo,verificacao_de_erro;
    char valor_atualizado[100];
   printf("\n===== ATUALIZAR DADOS DO ANIMAL =====\n");
    printf("Escolha o campo que deseja atualizar:\n");
    printf("1 - Nome\n");
    printf("2 - Raca\n");
    printf("3 - Faixa etaria\n");
    printf("4 - Apto para adocao (1 = Sim, 0 = Nao)\n");
    printf("======================================\n");
    printf("Digite a opcao desejada: ");
    scanf("%d", &atualizacao_de_atributo);
    limpar_buffer();


    switch (atualizacao_de_atributo){
    case 1:
        printf("\nEntre com o novo nome do animal: \n");
        fgets(valor_atualizado, sizeof(valor_atualizado), stdin);
        valor_atualizado[strcspn(valor_atualizado, "\n")] = '\0';
        verificacao_de_erro = atualizacao_geral(ponteiro_de_atualizacao,atualizacao_de_atributo,valor_atualizado);
        return verificacao_de_erro;
        break;
    case 2:
        printf("\nEntre com a nova Raca do animal: \n");
        printf("1 - Cachorro\n");
        printf("2 - Gato\n");
        printf("3 - Coelho\n");
        fgets(valor_atualizado, sizeof(valor_atualizado), stdin);
        valor_atualizado[strcspn(valor_atualizado, "\n")] = '\0';
        verificacao_de_erro = atualizacao_geral(ponteiro_de_atualizacao,atualizacao_de_atributo,valor_atualizado);
        return verificacao_de_erro;
        break;
    case 3:
        printf("\nEntre com a novo Faixa etaria do animal: \n");
        printf("1 - Recem nascido (menor de 1 ano)\n");
        printf("2 - Adulto (1-10 anos)\n");
        printf("3 - Velho (acima de 10 anos)\n");
        fgets(valor_atualizado, sizeof(valor_atualizado), stdin);
        valor_atualizado[strcspn(valor_atualizado, "\n")] = '\0';
        verificacao_de_erro = atualizacao_geral(ponteiro_de_atualizacao,atualizacao_de_atributo,valor_atualizado);
        return verificacao_de_erro;
        break;
    case 4:
        printf("\nEntre com a nova Disponibilidade para adocao do animal: \n");
        printf("\nO animal esta apto para adocao? 1-Sim 0-Nao\n");
        fgets(valor_atualizado, sizeof(valor_atualizado), stdin);
        valor_atualizado[strcspn(valor_atualizado, "\n")] = '\0';
        verificacao_de_erro = atualizacao_geral(ponteiro_de_atualizacao,atualizacao_de_atributo,valor_atualizado);
        return verificacao_de_erro;
        break;
    default:
    printf("\nOpcao Invalida!");
        return 0;
        break;
    }

    return 1;
}


int consulta_geral_animal() {
    bool resultado_verificacao;
    FILE *banco_de_animais = fopen("../data/animal.txt", "r");
    resultado_verificacao = verificacao_de_arquivo(banco_de_animais);
    if (resultado_verificacao == 0) {
        return 0;
    }

    char linha[300];

    printf("\n====================== LISTA DE ANIMAIS ======================\n");
    printf("%-5s | %-15s | %-10s | %-10s | %-10s\n",
           "ID", "Nome", "Especie", "Idade", "Adotado");
    printf("--------------------------------------------------------------\n");

    while (fgets(linha, sizeof(linha), banco_de_animais)) {
        linha[strcspn(linha, "\r\n")] = '\0';

        char *partes[10];
        int i = 0;
        char *token = strtok(linha, ";");

        while (token != NULL && i < 10) {
            partes[i++] = token;
            token = strtok(NULL, ";");
        }
        
        if (i == 5) {
            printf("%-5s | %-15s | %-10s | %-10s | %-10s\n",
                   partes[0], partes[1], partes[2], partes[3], partes[4]);
        }
    }

    printf("==============================================================\n");

    fclose(banco_de_animais);
    return 1;
}


int consulta_especifica_animal() {
    bool resultado_verificacao;
    FILE *banco_de_animais = fopen("../data/animal.txt", "r");
    resultado_verificacao = verificacao_de_arquivo(banco_de_animais);
    if (resultado_verificacao == 0) {
        return 0;
    }

    int id;
    printf("\nDigite o ID do animal que deseja consultar: ");
    scanf("%d", &id);

    char linha[200];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), banco_de_animais)) {
        char *token = strtok(linha, ";");
        char campos[5][50];
        int i = 0;

        while (token != NULL && i < 5) {
            strcpy(campos[i], token);
            token = strtok(NULL, ";");
            i++;
        }

        // verifica se o ID confere
        if (atoi(campos[0]) == id) {
            encontrado = 1;
            printf("\n================== DADOS DO ANIMAL ================================\n");
            printf("ID   | Nome                 | Raca | Faixa Etaria | Apto p/ Adocao\n");
            printf("----------------------------------------------------\n");
            printf("%-4s | %-20s | %-4s | %-13s | %-15s\n",
                   campos[0], campos[1], campos[2], campos[3], campos[4]);
            printf("===================================================================\n");
            break;
        }
    }

    if (!encontrado) {
        printf("\nNenhum animal encontrado com o ID informado.\n");
    }

    fclose(banco_de_animais);
    return 1;
}

