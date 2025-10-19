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