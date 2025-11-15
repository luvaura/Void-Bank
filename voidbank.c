#include <stdio.h>
#include "conta.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>

int main(){
    double valor_em_reais;
    long long valor_em_centavos;
    int opcao;
    conta_init();
    system("cls");

    do {
        
        printf("-+-+-+-+-VOID BANK-+-+-+-+-\n\n");
        printf("Seja bem-vindo(a)! Escolha entre as opcoes:\n");
        printf("1. Depositar (conta corrente)\n");
        printf("2. Sacar (sem cheque especial)\n");
        printf("3. Aplicar na poupanca\n");
        printf("4. Resgatar da poupanca\n");
        printf("5. Fazer PIX (registrar conta/chave de destino)\n");
        printf("6. Consultar saldos\n");
        printf("7. Extrato (listar transacoes com data/hora)\n");
        printf("8. Sair\n\n");
        
        scanf(" %d", &opcao);

        switch (opcao){
            case 1:
                
                printf("\nQual o valor do deposito?\nR$");
                scanf(" %lf", &valor_em_reais);

                valor_em_centavos = (long long)(valor_em_reais * 100 + 0.5);
                depositar(valor_em_centavos);
                system("cls");
                break;
                
            case 2:
                printf("\nQual o valor do saque?\nR$");
                scanf(" %lf", &valor_em_reais);
                valor_em_centavos = (long long)(valor_em_reais * 100 + 0.5);
                if (valor_em_centavos > saldo_corrente()){
                    printf("Saldo indisponivel.\n"); 
                }
                if (valor_em_centavos <= saldo_corrente()){
                    sacar(valor_em_centavos);
                }
                
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                printf("\nSaldo corrente: R$%.2f\n", saldo_corrente() / 100.0 );
                printf("Saldo poupanca: R$%.2f\n", saldo_poupanca() / 100.0 );
                printf("\nPressione ENTER para voltar ao menu.");
                while (getchar() != '\n');
                getchar();
                system("cls");
                break;
            case 7:
                extrato_imprimir();
                printf("\nPressione ENTER para voltar ao menu.");
                while (getchar() != '\n');
                getchar();
                system("cls");
                break;
            case 8:
                break;
        }


    } while (opcao != 8);


}