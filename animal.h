#ifndef animal_h
#define animal_h
#include <stdbool.h>

typedef struct{
    int identificador;
    char nome[50];
    char raca[50];
    int faixa_etaria;       // 1-Recem nascido, 2-Adulto, 3-Velho
    int apto_para_adocao;
}animal;

int cadastrar_animal();
#endif