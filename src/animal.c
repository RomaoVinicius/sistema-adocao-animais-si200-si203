#include "../include/animal.h"
#include "../include/utils.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
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

