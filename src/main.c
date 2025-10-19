#include <stdbool.h>
#include "../include/animal.h"
#include "../include/adotante.h"
#include "../include/utils.h"
#include <stdio.h>
#include <string.h>

int main(){
    int escolha_menu,verificacao_de_erro;
    char identificador_de_exclusao[100],cpf_de_exclusao[100];
    char *ponteiro_de_exclusao;
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
            printf("\nEntre com Identificador do animal a ser excluido do sistema\n");
            fgets(identificador_de_exclusao, sizeof(identificador_de_exclusao), stdin);
            identificador_de_exclusao[strcspn(identificador_de_exclusao, "\n")] = '\0';
            ponteiro_de_exclusao = identificador_de_exclusao;
            verificacao_de_erro = deletar_animal(ponteiro_de_exclusao);
            if(verificacao_de_erro == 1){
                printf("\nAnimal Exluido do Sistema;!");
            }else{
                printf("\nNao foi possivel excluir o animal");
            }
            break;
            case 4:
            printf("\nEntre com Cpf do Adotante a ser excluido do sistema\n");
            fgets(cpf_de_exclusao, sizeof(cpf_de_exclusao), stdin);
            cpf_de_exclusao[strcspn(cpf_de_exclusao, "\n")] = '\0';
            ponteiro_de_exclusao = cpf_de_exclusao;
            verificacao_de_erro = deletar_adotante(ponteiro_de_exclusao);
            if(verificacao_de_erro == 1){
                printf("\nAdotante foi Exluido do Sistema;!");
            }else{
                printf("\nNao foi possivel excluir o Adotante");
            }
            break;
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