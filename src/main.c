#include <stdbool.h>
#include "../include/animal.h"
#include "../include/adotante.h"
#include "../include/utils.h"
#include <stdio.h>

int main(){
    int escolha_menu,verificacao_de_erro;
    while (true){
        printf("\n===== MENU DO SISTEMA =====\n");
        printf("1 - Cadastrar animal\n");
        printf("2 - Cadastrar adotante\n");
        printf("3 - Excluir animal\n");
        printf("4 - Excluir adotante\n");
        printf("5 - Atualizar dados de um animal\n");
        printf("6 - Atualizar dados de um adotante\n");
        printf("7 - Consultar dados cadastrados de animais\n");
        printf("8 - Consultar dados cadastrados de adotantes\n");
        printf("9 - adotar\n");
        printf("10 - Consultar dados de adocao\n");
        printf("11 - Fechar sistema\n");
        printf("===========================\n");
        printf("Escolha uma opcao: ");
        scanf("%i",&escolha_menu);
        limpar_buffer();

        switch (escolha_menu){
            case 1:
            verificacao_de_erro = cadastrar_animal();
            if(verificacao_de_erro==1){
                printf("\nAnimal Cadastrado!");
            }else{
                printf("\nNao foi possivel cadastrar o animal");
            }
            break;

            case 2:
            verificacao_de_erro = cadastrar_adotante();
            if(verificacao_de_erro==1){
                printf("\nAdotante Cadastrado!");
            }else{
                printf("\nNao foi possivel cadastrar o Adotante");
            }
            break;
            
            case 3:
            break;
            case 4:
            break;
            case 5:
            break;
            case 6:
            break;
            case 7:
            break;
            case 8:
            case 9:
            break;
            case 10:
            break;
            case 11:
            printf("Finalizando Sistema...");
            return 0;
            default:
            printf("Escolha Invalida");
        }
    }
    
    return 0;
}