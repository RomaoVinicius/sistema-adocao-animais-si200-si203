#ifndef adotante_h
#define adotante_h

typedef struct{
    char nome[70];
    char cpf[30];
    char cep[30];
    char celular[30];
    int preferencia_de_raca;
    int faixaetaria;
}adotante;

int cadastrar_adotante();
int deletar_adotante(char *cpf_de_exclusao);
#endif