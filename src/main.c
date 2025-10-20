#include <stdbool.h>
#include "../include/animal.h"
#include "../include/adotante.h"
#include "../include/utils.h"
#include <stdio.h>
#include <string.h>

int main(){
    int escolha_menu,verificacao_de_erro,tipo_consulta;
    char identificador_de_exclusao[100],cpf_de_exclusao[100],identificador_de_atualizacao[100],cpf_de_atualizacao[100];
    char *ponteiro_de_exclusao;
    char *ponteiro_de_atualizacao;
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
            case 5:
            printf("\nEntre com id do Animal a ser atualizacao no sistema\n");
            fgets(identificador_de_atualizacao, sizeof(identificador_de_atualizacao), stdin);
            identificador_de_atualizacao[strcspn(identificador_de_atualizacao, "\n")] = '\0';
            ponteiro_de_atualizacao = identificador_de_atualizacao;

            verificacao_de_erro = atualizaco_de_animal(ponteiro_de_atualizacao);
            if(verificacao_de_erro == 1){
                printf("\nAnimal atualizado!");
            }else{
                printf("\nNao foi possivel Atualizar o Animal");
            }
            break;
            case 6:
            printf("\nEntre com Cpf do Adotante a ser atualizacao no sistema\n");
            fgets(cpf_de_atualizacao, sizeof(cpf_de_atualizacao), stdin);
            cpf_de_atualizacao[strcspn(cpf_de_atualizacao, "\n")] = '\0';
            ponteiro_de_atualizacao = cpf_de_atualizacao;

            verificacao_de_erro = atualizaco_de_adotante(ponteiro_de_atualizacao);
            if(verificacao_de_erro == 1){
                printf("\nAdotante atualizado!");
            }else{
                printf("\nNao foi possivel Atualizar o Adotante");
            }
            break;
            case 7:
            printf("\nDeseja fazer um 1 - consulta geral ou 2 -especifica ?\n");
            scanf("%i",&tipo_consulta);
            limpar_buffer();
            if(tipo_consulta==1){
               verificacao_de_erro = consulta_geral_animal(); 
            }else{
                verificacao_de_erro = consulta_especifica_animal();
            }
            if(verificacao_de_erro != 1){
                printf("\nNao foi possivel Fazer a consulta");
            }
            break;

            case 8:
            printf("\nDeseja fazer um 1 - consulta geral ou 2 -especifica ?\n");
            scanf("%i",&tipo_consulta);
            limpar_buffer();
            if(tipo_consulta==1){
               verificacao_de_erro = consulta_geral_adotante(); 
            }else{
                verificacao_de_erro = consulta_especifica_adotante();
            }
            if(verificacao_de_erro != 1){
                printf("\nNao foi possivel Fazer a consulta");
            }
            break;
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