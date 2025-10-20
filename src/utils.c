#include "../include/utils.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


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
