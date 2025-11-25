#include <stdio.h>
#include "conta.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

int main(){
    double valor_em_reais;
    long long valor_em_centavos;
    int opcao;
    int status;
    conta_init();
    system("cls");

    do {
        
        printf("-+-+-+-+-VOID BANK-+-+-+-+-\n\n");
        printf("Seja bem-vindo(a)! Escolha entre as opcoes:\n");
        printf("1. Depositar (conta corrente)\n");
        printf("2. Sacar\n");
        printf("3. Aplicar na poupanca\n");
        printf("4. Resgatar da poupanca\n");
        printf("5. Fazer PIX\n");
        printf("6. Consultar saldos\n");
        printf("7. Extrato\n");
        printf("8. Sair\n\n");
        
        scanf(" %d", &opcao);

        switch (opcao){
                
            case 1: // Deposito
                printf("\nQual o valor do deposito?\nR$");
                scanf(" %lf", &valor_em_reais);
                valor_em_centavos = (long long)round(valor_em_reais * 100);
                status = depositar(valor_em_centavos);
                if (status == ERRO_CAPACIDADE_LOG){
                    printf("Limite de transacoes atingido. \n");
                    printf("[ALERTA] Capacidade de registros atingida (100 transações).\n");
                    printf("O serviço do VoidBank sairá do ar agora.\n");
                    return 0;
                } else if (status == OK){
                    printf("Deposito de R$%.2f realizado com sucesso!\n", valor_em_reais);
                } else if (status == ERRO_VALOR_INVALIDO){
                    printf("Valor invalido para deposito.\n");
                }
                printf("\nPressione ENTER para voltar ao menu.");
                while (getchar() != '\n');
                getchar();
                system("cls");
                break;

                
            case 2: 
                printf("\nQual o valor do saque?\nR$");
                scanf(" %lf", &valor_em_reais);
                valor_em_centavos = (long long)round(valor_em_reais * 100);
                status = sacar(valor_em_centavos);
                if (status == ERRO_SALDO_INSUFICIENTE){
                    printf("Saldo indisponivel.\n"); 
                } else if (status == ERRO_CAPACIDADE_LOG){
                    printf("Limite de transacoes atingido. \n");
                    printf("[ALERTA] Capacidade de registros atingida (100 transações).\n");
                    printf("O serviço do VoidBank sairá do ar agora.\n");
                    return 0;
                } else if (status == OK){
                    printf("Saque de R$%.2f realizado com sucesso!\n", valor_em_reais);
                } else if (status == ERRO_VALOR_INVALIDO){
                    printf("Valor invalido para saque.\n");
                }
                printf("\nPressione ENTER para voltar ao menu.");
                while (getchar() != '\n');
                getchar();
                system("cls");
                break;
                
            case 3: 
                printf("\nQual o valor a ser aplicado na poupanca?\nR$"); 
                scanf(" %lf", &valor_em_reais);
                valor_em_centavos = (long long)round(valor_em_reais * 100);
                status = aplicar_poupanca(valor_em_centavos);
                if (status == ERRO_SALDO_INSUFICIENTE){
                    printf("Saldo indisponivel.\n"); 
                } else if (status == ERRO_CAPACIDADE_LOG){
                    printf("Limite de transacoes atingido. \n");
                    printf("[ALERTA] Capacidade de registros atingida (100 transações).\n");
                    printf("O serviço do VoidBank sairá do ar agora.\n");
                    return 0;

                } else if (status == OK){
                    printf("Aplique de R$%.2f realizado com sucesso!\n", valor_em_reais);
                } else if (status == ERRO_VALOR_INVALIDO){
                    printf("Valor invalido para aplicacao.\n");
                }
                printf("\nPressione ENTER para voltar ao menu.");
                while (getchar() != '\n');
                getchar();
                system("cls");
                break; // Aplicar poupanca
                
            case 4: // Resgatar poupanca
                printf("\nQual o valor a ser rasgatado na poupanca?\n R$");
                scanf(" %lf", &valor_em_reais);
                valor_em_centavos = (long long)round(valor_em_reais * 100);
                status = resgatar_poupanca(valor_em_centavos);
                if (status == ERRO_SALDO_INSUFICIENTE){
                    printf("Saldo indisponivel.\n"); 
                } else if (status == ERRO_CAPACIDADE_LOG){
                    printf("Limite de transacoes atingido. \n");
                    printf("[ALERTA] Capacidade de registros atingida (100 transações).\n");
                    printf("O serviço do VoidBank sairá do ar agora.\n");
                    return 0;

                } else if (status == OK){
                    printf("Resgate de R$%.2f realizado com sucesso!\n", valor_em_reais);
                } else if (status == ERRO_VALOR_INVALIDO){
                    printf("Valor invalido para resgate.\n");
                }
                printf("\nPressione ENTER para voltar ao menu.");
                while (getchar() != '\n');
                getchar();
                system("cls");
                break;
                
            case 5: // Fazer o Pix
                printf("\nQual o valor da transferencia pix?\nR$");
                scanf(" %lf", &valor_em_reais);
                char chave[20];
                printf("\nQual a chave pix?\n");
                scanf(" %s", chave);
                valor_em_centavos = (long long)round(valor_em_reais * 100);
                status = fazer_pix(chave, valor_em_centavos);
                if (status == ERRO_SALDO_INSUFICIENTE){
                    printf("Saldo indisponivel.\n"); 
                } else if (status == ERRO_CAPACIDADE_LOG){
                    printf("Limite de transacoes atingido. \n");
                    printf("[ALERTA] Capacidade de registros atingida (100 transações).\n");
                    printf("O serviço do VoidBank sairá do ar agora.\n");
                    return 0;

                } else if (status == OK){
                    printf("Pix de R$%.2f realizado com sucesso!\n", valor_em_reais);
                } else if (status == ERRO_VALOR_INVALIDO){
                    printf("Valor invalido para pix.\n");
                }
                printf("\nPressione ENTER para voltar ao menu.");
                while (getchar() != '\n');
                getchar();
                system("cls");
                break;

            case 6: // Consultar saldo
                printf("\nSaldo corrente: R$%.2f\n", saldo_corrente() / 100.0 );
                printf("Saldo poupanca: R$%.2f\n", saldo_poupanca() / 100.0 );
                printf("\nPressione ENTER para voltar ao menu.");
                while (getchar() != '\n');
                getchar();
                system("cls");
                break;

            case 7: // Extrato
                extrato_imprimir();
                printf("\nPressione ENTER para voltar ao menu.");
                while (getchar() != '\n');
                getchar();
                system("cls");
                break;

            case 8: // Sair
                break;


            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                printf("\nPressione ENTER para voltar ao menu.");
                while (getchar() != '\n');
                getchar();
                system("cls");
                break;
        }


    } while (opcao != 8);


}