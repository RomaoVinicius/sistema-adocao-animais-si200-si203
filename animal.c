#include "animal.h"
#include <stdio.h>
#include "utils.h"
#include <stdbool.h>
#include <string.h> 
int cadastrar_animal(){
    bool resultado_verificacao;
    FILE *banco_de_animais = fopen("animal.txt","a+");
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
    while (getchar() != '\n'); 
    fgets(cadastro_animal.nome, sizeof(cadastro_animal.nome), stdin);
    cadastro_animal.nome[strcspn(cadastro_animal.nome, "\n")] = '\0';

    printf("\nentre com a Raca do animal : ");
    fgets(cadastro_animal.raca, sizeof(cadastro_animal.raca), stdin);
    cadastro_animal.raca[strcspn(cadastro_animal.raca, "\n")] = '\0';
    do {
        printf("\nDigite a faixa etaria do animal:\n");
        printf("1 - Recem nascido (menor de 1 ano)\n");
        printf("2 - Adulto (1-10 anos)\n");
        printf("3 - Velho (acima de 10 anos)\n");
        scanf("%d", &cadastro_animal.faixa_etaria);
        while (getchar() != '\n'); 
        if (cadastro_animal.faixa_etaria < 1 || cadastro_animal.faixa_etaria > 3) {
            printf("Erro: faixa etaria invalida. Tente novamente.\n");
        }
        
    } while (cadastro_animal.faixa_etaria < 1 || cadastro_animal.faixa_etaria > 3);

     do {
        printf("\nO animal esta apto para adocao? 1-Sim 0-Nao\n");
        scanf("%d", &cadastro_animal.apto_para_adocao);
        while (getchar() != '\n'); // limpar buffer do teclado
        if (cadastro_animal.apto_para_adocao != 0 && cadastro_animal.apto_para_adocao != 1) {
            printf("\nErro: valor invalido. Tente novamente.\n");
        }
    } while (cadastro_animal.apto_para_adocao != 0 && cadastro_animal.apto_para_adocao != 1);

    fprintf(banco_de_animais, "%d;%s;%s;%d;%d\n",
            cadastro_animal.identificador,
            cadastro_animal.nome,
            cadastro_animal.raca,
            cadastro_animal.faixa_etaria,
            cadastro_animal.apto_para_adocao);

    fclose(banco_de_animais);
    return 1;
}