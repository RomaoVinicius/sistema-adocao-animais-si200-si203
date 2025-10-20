#include "../include/utils.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

int verificacao_de_arquivo(FILE *banco_de_animais){
    if(banco_de_animais==NULL){
        printf("ERRO! no banco de Dados");
        return 0;
    }else{
        return 1;
    }
}

void limpar_buffer(){
    while (getchar() != '\n');
}

int atualizacao_geral(char *ponteiro_de_atualizacao, int atributo_atualizado, char *valor_atualizado) {
    FILE *banco_temp;
    FILE *banco;

    // Decide qual arquivo abrir baseado no atributo
    int eh_animal = (atributo_atualizado >= 1 && atributo_atualizado <= 4);
    if (eh_animal) {
        banco = fopen("../data/animal.txt", "r");
        banco_temp = fopen("../data/animal_temp.txt", "w");
    } else {
        banco = fopen("../data/adotantes.txt", "r");
        banco_temp = fopen("../data/adotantes_temp.txt", "w");
    }

    if (!banco || !banco_temp) {
        printf("Erro ao abrir arquivos.\n");
        return 0;
    }

    char linha[300];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), banco)) {
        linha[strcspn(linha, "\r\n")] = '\0'; // remove quebra de linha
        char primeira_palavra[100];
        int i = 0;

        // Lê até o primeiro ';'
        while (linha[i] != ';' && linha[i] != '\0') {
            primeira_palavra[i] = linha[i];
            i++;
        }
        primeira_palavra[i] = '\0';

        // Remove espaços extras (importante!)
        while (isspace((unsigned char)primeira_palavra[strlen(primeira_palavra) - 1])) {
            primeira_palavra[strlen(primeira_palavra) - 1] = '\0';
        }

        if (strcmp(primeira_palavra, ponteiro_de_atualizacao) == 0) {
            encontrado = 1;

            char *partes[10];
            int j = 0;
            char *token = strtok(linha, ";");
            while (token && j < 10) {
                partes[j++] = token;
                token = strtok(NULL, ";");
            }

            int indice_real;
            if (eh_animal)
                indice_real = atributo_atualizado;
            else
                indice_real = atributo_atualizado - 4;

            if (indice_real >= 1 && indice_real <= j) {
                partes[indice_real - 1] = valor_atualizado;
            }

            for (int k = 0; k < j; k++) {
                fprintf(banco_temp, "%s", partes[k]);
                if (k < j - 1) fprintf(banco_temp, ";");
            }
            fprintf(banco_temp, "\n");

        } else {
            fprintf(banco_temp, "%s\n", linha);
        }
    }

    fclose(banco);
    fclose(banco_temp);

    if (eh_animal) {
        remove("../data/animal.txt");
        rename("../data/animal_temp.txt", "../data/animal.txt");
    } else {
        remove("../data/adotantes.txt");
        rename("../data/adotantes_temp.txt", "../data/adotantes.txt");
    }

    return encontrado;
}

int adocao_de_animal(char *cpf) {
    FILE *banco_de_animais = fopen("../data/animal.txt", "r");
    FILE *banco_de_adotantes = fopen("../data/adotantes.txt", "r");
    FILE *banco_de_adocoes = fopen("../data/adocoes.txt", "a+");

    if (!banco_de_animais || !banco_de_adotantes || !banco_de_adocoes) {
        printf("Erro ao abrir um dos arquivos necessarios.\n");
        return 0;
    }

    
    char linha[300];
    int adotante_encontrado = 0;

    while (fgets(linha, sizeof(linha), banco_de_adotantes)) {
        linha[strcspn(linha, "\r\n")] = '\0'; 
        char *token = strtok(linha, ";");
        if (token != NULL && strcmp(token, cpf) == 0) {
            adotante_encontrado = 1;
            break;
        }
    }

    if (!adotante_encontrado) {
        printf("\nAdotante nao encontrado. Cadastre-o antes de realizar a adocao.\n");
        fclose(banco_de_animais);
        fclose(banco_de_adotantes);
        fclose(banco_de_adocoes);
        return 0;
    }


    rewind(banco_de_animais);
    printf("\n=========== ANIMAIS DISPONIVEIS PARA ADOCAO ===========\n");
    printf("ID | Nome                | Tipo | Idade | Apto\n");
    printf("-------------------------------------------------------\n");

    int animais_disponiveis = 0;
    while (fgets(linha, sizeof(linha), banco_de_animais)) {
        linha[strcspn(linha, "\r\n")] = '\0';
        char *token = strtok(linha, ";");
        char campos[6][50];
        int i = 0;

        while (token != NULL && i < 6) {
            strcpy(campos[i++], token);
            token = strtok(NULL, ";");
        }

        if (atoi(campos[4]) == 1) { // apto para adocao
            printf("%-3s | %-18s | %-4s | %-5s | %-3s\n",
                   campos[0], campos[1], campos[2], campos[3], campos[4]);
            animais_disponiveis++;
        }
    }

    if (animais_disponiveis == 0) {
        printf("\nNao ha animais disponiveis para adocao no momento.\n");
        fclose(banco_de_animais);
        fclose(banco_de_adotantes);
        fclose(banco_de_adocoes);
        return 0;
    }

    
    int id_escolhido;
    printf("\nDigite o ID do animal que deseja adotar: ");
    scanf("%d", &id_escolhido);

    
    fprintf(banco_de_adocoes, "%s;%d;\n", cpf, id_escolhido);
    printf("\nAdocao registrada com sucesso!\n");

    
    rewind(banco_de_animais);
    FILE *temp = fopen("../data/temp.txt", "w");

    if (!temp) {
        printf("Erro ao criar arquivo temporario.\n");
        fclose(banco_de_animais);
        fclose(banco_de_adotantes);
        fclose(banco_de_adocoes);
        return 0;
    }

    while (fgets(linha, sizeof(linha), banco_de_animais)) {
        linha[strcspn(linha, "\r\n")] = '\0';
        char *token = strtok(linha, ";");
        char campos[6][50];
        int i = 0;

        while (token != NULL && i < 6) {
            strcpy(campos[i++], token);
            token = strtok(NULL, ";");
        }

        // marca como nao apto
        if (atoi(campos[0]) == id_escolhido) {
            strcpy(campos[4], "0");
        }

        fprintf(temp, "%s;%s;%s;%s;%s\n",
                campos[0], campos[1], campos[2], campos[3], campos[4]);
    }

    fclose(banco_de_animais);
    fclose(temp);
    remove("../data/animal.txt");
    rename("../data/temp.txt", "../data/animal.txt");

    fclose(banco_de_adotantes);
    fclose(banco_de_adocoes);

    return 1;
}
