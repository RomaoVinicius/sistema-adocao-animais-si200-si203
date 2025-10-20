#ifndef utils_h
#define utils_h
#include <stdbool.h>
#include <stdio.h>
int verificacao_de_arquivo(FILE *banco_de_animais);
void limpar_buffer();
int atualizacao_geral(char *ponteiro_de_atualizacao, int atributo_atualizado, char *valor_atualizado);
#endif