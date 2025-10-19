#ifndef adotante_h
#define adotante_h

typedef struct{
    char nome[70];
    char cpf[12];
    char cep[9];
    char celular[20];
    int preferencia_de_raca;
    int faixaetaria;
}adotante;

int cadastrar_adotante();
#endif