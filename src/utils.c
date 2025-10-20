#include "../include/utils.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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

    if (atributo_atualizado >= 1 && atributo_atualizado <= 4) {
        banco_temp = fopen("../data/animal_temp.txt", "w");
        banco = fopen("../data/animal.txt", "r");
    } else {
        banco_temp = fopen("../data/adotantes_temp.txt", "w");
        banco = fopen("../data/adotantes.txt", "r");
    }

    if (banco == NULL || banco_temp == NULL) {
        printf("Erro ao abrir arquivos.\n");
        return 0;
    }

    char identificador_da_linha[300];
    int encontrado = 0;

    while (fgets(identificador_da_linha, sizeof(identificador_da_linha), banco)) {
        identificador_da_linha[strcspn(identificador_da_linha, "\n")] = '\0';
        char primeira_palavra[100];
        int i = 0;

        
        while (identificador_da_linha[i] != ';' && identificador_da_linha[i] != '\0' && identificador_da_linha[i] != '\n') {
            primeira_palavra[i] = identificador_da_linha[i];
            i++;
        }
        primeira_palavra[i] = '\0';

        if (strcmp(primeira_palavra, ponteiro_de_atualizacao) == 0) {
            encontrado = 1;
            char *partes[10];
            int j = 0;
            char *token = strtok(identificador_da_linha, ";");

            while (token != NULL && j < 10) {
                partes[j++] = token;
                //Continue de onde parou e me dá o próximo pedaço até o próximo ;
                token = strtok(NULL, ";");
            }

            // Atualiza o atributo escolhido
            if (atributo_atualizado >= 1 && atributo_atualizado <= j) {
                partes[atributo_atualizado] = valor_atualizado;
            }

            // Regrava a linha atualizada
                for (int k = 0; k < j; k++) {
                fprintf(banco_temp, "%s", partes[k]);
                if (k < j - 1) fprintf(banco_temp, ";");  // adiciona ; só entre os campos
                }
            fprintf(banco_temp, "\n");  

        } else {
            // Mantém a linha original
            fprintf(banco_temp, "%s\n", identificador_da_linha);
        }
    }

    fclose(banco);
    fclose(banco_temp);

    if (atributo_atualizado >= 1 && atributo_atualizado <= 4) {
        remove("../data/animal.txt");
        rename("../data/animal_temp.txt", "../data/animal.txt");
    } else {
        remove("../data/adotantes.txt");
        rename("../data/adotantes_temp.txt", "../data/adotantes.txt");
    }

    return encontrado;
}
