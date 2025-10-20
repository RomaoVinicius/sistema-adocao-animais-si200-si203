#include "../include/adotante.h"
#include "../include/utils.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int cadastrar_adotante() {
    bool resultado_verificacao;
    FILE *banco_de_adotantes = fopen("../data/adotantes.txt", "a+");
    resultado_verificacao = verificacao_de_arquivo(banco_de_adotantes);
    if (resultado_verificacao == 0) {
        return 0;
    }

    adotante cadastro_adotante;
    printf("\nEntre com o nome do adotante: ");
    fgets(cadastro_adotante.nome, sizeof(cadastro_adotante.nome), stdin);
    cadastro_adotante.nome[strcspn(cadastro_adotante.nome, "\n")] = '\0';

    printf("\nEntre com o CPF do adotante: ");
    fgets(cadastro_adotante.cpf, sizeof(cadastro_adotante.cpf), stdin);
    cadastro_adotante.cpf[strcspn(cadastro_adotante.cpf, "\n")] = '\0';

    printf("\nEntre com o CEP do adotante: ");
    fgets(cadastro_adotante.cep, sizeof(cadastro_adotante.cep), stdin);
    cadastro_adotante.cep[strcspn(cadastro_adotante.cep, "\n")] = '\0';

    printf("\nEntre com o numero de telefone para contato do adotante: ");
    fgets(cadastro_adotante.celular, sizeof(cadastro_adotante.celular), stdin);
    cadastro_adotante.celular[strcspn(cadastro_adotante.celular, "\n")] = '\0';

    printf("\nEntre com a especie que o adotante pretende adotar:\n");
    printf("1 - Cachorro\n");
    printf("2 - Gato\n");
    printf("3 - Coelho\n");
    scanf("%i", &cadastro_adotante.preferencia_de_raca);
    limpar_buffer();

    printf("\nEntre com a faixa etaria que o adotante pretende adotar:\n");
    printf("1 - Recem-nascido (menor de 1 ano)\n");
    printf("2 - Adulto (1 a 10 anos)\n");
    printf("3 - Idoso (acima de 10 anos)\n");
    scanf("%i", &cadastro_adotante.faixaetaria);
    limpar_buffer();

    fprintf(banco_de_adotantes, "%s;%s;%s;%s;%i;%i\n",
            cadastro_adotante.cpf,
            cadastro_adotante.nome,
            cadastro_adotante.cep,
            cadastro_adotante.celular,
            cadastro_adotante.preferencia_de_raca,
            cadastro_adotante.faixaetaria);

    fclose(banco_de_adotantes);
    return 1;
}


int deletar_adotante(char *cpf_de_exclusao){
        // criacao de 1 arquivo copia para apagar o animal
        FILE *banco_de_adotantes = fopen("../data/adotantes.txt", "r");
        FILE *banco_de_adotantes_temp = fopen("../data/adotantes_temp.txt", "w");
        char cpf_da_linha[200];
        int encontrado = 0;

        if (banco_de_adotantes == NULL || banco_de_adotantes_temp == NULL) {
        return 0;
        }

        while (fgets(cpf_da_linha, sizeof(cpf_da_linha), banco_de_adotantes)) {
        char primeira_palavra[100];
        int i = 0;

        while (cpf_da_linha[i] != ';' && cpf_da_linha[i] != '\0' && cpf_da_linha[i] != '\n') {
        primeira_palavra[i] = cpf_da_linha[i];
        i++;
        }
        primeira_palavra[i] = '\0';

        if (strcmp(primeira_palavra, cpf_de_exclusao) == 0) {
        encontrado = 1;
        } else {
        fputs(cpf_da_linha, banco_de_adotantes_temp);
    }
}

    fclose(banco_de_adotantes);
    fclose(banco_de_adotantes_temp);

    remove("../data/adotantes.txt");
    rename("../data/adotantes_temp.txt", "../data/adotantes.txt");

    return encontrado;
}


int atualizaco_de_adotante(char *ponteiro_de_atualizacao){
    int atualizacao_de_atributo,verificacao_de_erro;
    char valor_atualizado[100];
    printf("\n===== ATUALIZAR DADOS DO ADOTANTE =====\n");
    printf("Escolha o campo que deseja atualizar:\n");
    printf("1 - CPF\n");
    printf("2 - nome\n");
    printf("3 - CEP\n");
    printf("4 - Celular\n");
    printf("5 - Preferencia de raca\n");
    printf("6 - Faixa etaria desejada do animal\n");
    printf("=======================================\n");
    printf("Digite a opcao desejada: ");

    scanf("%d", &atualizacao_de_atributo);
    limpar_buffer();

    switch (atualizacao_de_atributo){
    case 1:
        printf("\nEntre com o nvo nome do adotante: ");
        fgets(valor_atualizado, sizeof(valor_atualizado), stdin);
        valor_atualizado[strcspn(valor_atualizado, "\n")] = '\0';
        verificacao_de_erro = atualizacao_geral(ponteiro_de_atualizacao,atualizacao_de_atributo+4,valor_atualizado);
        break;
    case 2:
        printf("\nEntre com o novo CPF do adotante: ");
        fgets(valor_atualizado, sizeof(valor_atualizado), stdin);
        valor_atualizado[strcspn(valor_atualizado, "\n")] = '\0';
        verificacao_de_erro = atualizacao_geral(ponteiro_de_atualizacao,atualizacao_de_atributo+4,valor_atualizado);
        break;
    case 3:
        printf("\nEntre com o novo CEP do adotante: ");
        fgets(valor_atualizado, sizeof(valor_atualizado), stdin);
        valor_atualizado[strcspn(valor_atualizado, "\n")] = '\0';
        verificacao_de_erro = atualizacao_geral(ponteiro_de_atualizacao,atualizacao_de_atributo+4,valor_atualizado);
        break;
    case 4:
        printf("\nEntre com o novo numero de telefone para contato do adotante: ");
        fgets(valor_atualizado, sizeof(valor_atualizado), stdin);
        valor_atualizado[strcspn(valor_atualizado, "\n")] = '\0';
        verificacao_de_erro = atualizacao_geral(ponteiro_de_atualizacao,atualizacao_de_atributo+4,valor_atualizado);
        break;
    case 5:
        printf("\nEntre com a nova especie que o adotante pretende adotar:\n");
        printf("1 - Cachorro\n");
        printf("2 - Gato\n");
        printf("3 - Coelho\n");
        fgets(valor_atualizado, sizeof(valor_atualizado), stdin);
        valor_atualizado[strcspn(valor_atualizado, "\n")] = '\0';
        verificacao_de_erro = atualizacao_geral(ponteiro_de_atualizacao,atualizacao_de_atributo+4,valor_atualizado);
        break;
    case 6:
        printf("\nEntre com a nova faixa etaria que o adotante pretende adotar:\n");
        printf("1 - Recem-nascido (menor de 1 ano)\n");
        printf("2 - Adulto (1 a 10 anos)\n");
        printf("3 - Idoso (acima de 10 anos)\n");
        fgets(valor_atualizado, sizeof(valor_atualizado), stdin);
        valor_atualizado[strcspn(valor_atualizado, "\n")] = '\0';
        verificacao_de_erro = atualizacao_geral(ponteiro_de_atualizacao,atualizacao_de_atributo+4,valor_atualizado);
        break;
    default:
    printf("\nOpcao Invalida!");
        return 0;
        break;
    }

    return verificacao_de_erro;
}

int consulta_geral_adotante() {
    bool resultado_verificacao;
    FILE *banco_de_adotantes = fopen("../data/adotantes.txt", "r");
    resultado_verificacao = verificacao_de_arquivo(banco_de_adotantes);
    if (resultado_verificacao == 0) {
        return 0;
    }

    char linha[300];

    printf("\n====================== LISTA DE ADOTANTES =========================================================\n");
    printf("%-15s | %-25s | %-10s | %-12s | %-10s | %-10s\n",
           "CPF", "Nome", "CEP", "Celular", "Raca", "Faixa Etaria");
    printf("----------------------------------------------------------------\n");

    while (fgets(linha, sizeof(linha), banco_de_adotantes)) {
        // Remove quebras de linha (\n e \r)
        linha[strcspn(linha, "\r\n")] = '\0';

        char *partes[10];
        int i = 0;
        char *token = strtok(linha, ";");

        while (token != NULL && i < 10) {
            partes[i++] = token;
            token = strtok(NULL, ";");
        }

        // So mostra se tiver pelo menos 6 campos
        if (i >= 6) {
            printf("%-15s | %-25s | %-10s | %-12s | %-10s | %-10s\n",
                   partes[0], partes[1], partes[2], partes[3], partes[4], partes[5]);
        } else {
            printf("[ERRO] Linha com formato incorreto: %s\n", linha);
        }
    }

    printf("==================================================================================================\n");

    fclose(banco_de_adotantes);
    return 1;
}


int consulta_especifica_adotante() {
    bool resultado_verificacao;
    FILE *banco_de_adotantes = fopen("../data/adotantes.txt", "r");
    resultado_verificacao = verificacao_de_arquivo(banco_de_adotantes);
    if (resultado_verificacao == 0) {
        return 0;
    }

    char cpf[20];
    printf("\nDigite o CPF do adotante que deseja consultar: ");
    scanf("%19s", cpf);

    char linha[300];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), banco_de_adotantes)) {
        linha[strcspn(linha, "\r\n")] = '\0';

        char *partes[10];
        int i = 0;
        char *token = strtok(linha, ";");

        while (token != NULL && i < 10) {
            partes[i++] = token;
            token = strtok(NULL, ";");
        }

        if (strcmp(partes[0], cpf) == 0) {
            encontrado = 1;

            printf("\n================== DADOS DO ADOTANTE =============================================================\n");
            printf("%-15s | %-25s | %-10s | %-12s | %-10s | %-10s\n",
                   "CPF", "Nome", "CEP", "Celular", "Raca", "Faixa Etaria");
            printf("-------------------------------------------------------\n");
            printf("%-15s | %-25s | %-10s | %-12s | %-10s | %-10s\n",
                   partes[0], partes[1], partes[2], partes[3], partes[4], partes[5]);
            printf("===============================================================================================\n");
            break;
        }
    }

    if (!encontrado) {
        printf("\nNenhum adotante encontrado com o CPF informado.\n");
    }

    fclose(banco_de_adotantes);
    return 1;
}
