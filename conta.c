#include <stdio.h>
#include "conta.h"
#include <string.h>
#include <time.h>
#include <math.h>

Conta minha_conta;

void data_horario(char datahorario[], int tamanho) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    strftime(datahorario, tamanho, "%Y-%m-%d %H:%M:%S", tm);
}

void conta_init(void){
    minha_conta.saldo_corrente = 0;
    minha_conta.saldo_poupanca = 0;
    minha_conta.nlog = 0;
}

int depositar(long long valor){
    if (valor <= 0){
        return ERRO_VALOR_INVALIDO;
    }

    if (minha_conta.nlog >= MAX_TRANS){
        return ERRO_CAPACIDADE_LOG;
    }
    minha_conta.saldo_corrente += valor;
    minha_conta.log[minha_conta.nlog].tipo = DEP;
    minha_conta.log[minha_conta.nlog].valor = valor;
    minha_conta.log[minha_conta.nlog].saldo_corrente_apos = minha_conta.saldo_corrente;
    minha_conta.log[minha_conta.nlog].saldo_poupanca_apos = minha_conta.saldo_poupanca;
    data_horario(minha_conta.log[minha_conta.nlog].quando, 20);
    minha_conta.nlog ++;
    return OK;
}

int sacar(long long valor){
    if (valor <= 0){
        return ERRO_VALOR_INVALIDO;
    }

    if (valor > minha_conta.saldo_corrente){
        return ERRO_SALDO_INSUFICIENTE;
    }

    if (minha_conta.nlog >= MAX_TRANS){
        return ERRO_CAPACIDADE_LOG;
    }

    minha_conta.saldo_corrente -= valor;
    minha_conta.log[minha_conta.nlog].tipo = SAQ;
    minha_conta.log[minha_conta.nlog].valor = valor;
    minha_conta.log[minha_conta.nlog].saldo_corrente_apos = minha_conta.saldo_corrente;
    minha_conta.log[minha_conta.nlog].saldo_poupanca_apos = minha_conta.saldo_poupanca;
    data_horario(minha_conta.log[minha_conta.nlog].quando, 20);
    minha_conta.nlog ++;

    return OK;
}

int aplicar_poupanca(long long valor){
    if (valor <= 0){
        return ERRO_VALOR_INVALIDO;
    }

    if (valor > minha_conta.saldo_corrente){
        return ERRO_SALDO_INSUFICIENTE;
    }

    if (minha_conta.nlog >= MAX_TRANS){
        return ERRO_CAPACIDADE_LOG;
    }
    minha_conta.saldo_corrente -= valor;
    minha_conta.saldo_poupanca += valor;
    minha_conta.log[minha_conta.nlog].tipo = APLI;
    minha_conta.log[minha_conta.nlog].valor = valor;
    minha_conta.log[minha_conta.nlog].saldo_corrente_apos = minha_conta.saldo_corrente;
    minha_conta.log[minha_conta.nlog].saldo_poupanca_apos = minha_conta.saldo_poupanca;
    data_horario(minha_conta.log[minha_conta.nlog].quando, 20);
    minha_conta.nlog ++;

    return OK;
} // passar dinheiro da conta para a poupanca

int resgatar_poupanca(long long valor){
    if (valor <= 0){
        return ERRO_VALOR_INVALIDO;
    }

    if (valor > minha_conta.saldo_poupanca){
        return ERRO_SALDO_INSUFICIENTE;
    }

    if (minha_conta.nlog >= MAX_TRANS){
        return ERRO_CAPACIDADE_LOG;
    }
    minha_conta.saldo_corrente += valor;
    minha_conta.saldo_poupanca -= valor;
    minha_conta.log[minha_conta.nlog].tipo = RESG;
    minha_conta.log[minha_conta.nlog].valor = valor;
    minha_conta.log[minha_conta.nlog].saldo_corrente_apos = minha_conta.saldo_corrente;
    minha_conta.log[minha_conta.nlog].saldo_poupanca_apos = minha_conta.saldo_poupanca;
    data_horario(minha_conta.log[minha_conta.nlog].quando, 20);
    minha_conta.nlog ++;
    return OK;
} //passar dinheiro da poupanca para a conta

int fazer_pix(const char destino[], long long valor){
    if (valor <= 0){
        return ERRO_VALOR_INVALIDO;
    }

    if (valor > minha_conta.saldo_corrente){
        return ERRO_SALDO_INSUFICIENTE;
    }

    if (minha_conta.nlog >= MAX_TRANS){
        return ERRO_CAPACIDADE_LOG;
    }
    minha_conta.saldo_corrente -= valor;
    minha_conta.log[minha_conta.nlog].tipo = PIX;
    minha_conta.log[minha_conta.nlog].valor = valor;
    minha_conta.log[minha_conta.nlog].saldo_corrente_apos = minha_conta.saldo_corrente;
    minha_conta.log[minha_conta.nlog].saldo_poupanca_apos = minha_conta.saldo_poupanca;
    strncpy(minha_conta.log[minha_conta.nlog].destino, destino, 127);
    minha_conta.log[minha_conta.nlog].destino[127] = '\0';
    data_horario(minha_conta.log[minha_conta.nlog].quando, 20);
    minha_conta.nlog ++;
    return OK;
} //tirar dinheiro da conta e transferir para a chave pix



long long saldo_corrente(void){
    return minha_conta.saldo_corrente;
} //retorna o valor do saldo corrente

long long saldo_poupanca(void){
    return minha_conta.saldo_poupanca;
} //retorna o valor da poupança

void extrato_imprimir(void){
    for (int i = 0; i < minha_conta.nlog; i++){
        printf("\nTransacao #%d\n", i + 1);
        switch (minha_conta.log[i].tipo){
            case DEP:
                printf("Tipo de transacao: Deposito\n");
                break;
            case SAQ:
                printf("Tipo de transacao: Saque\n");
                break;
            case APLI:
                printf("Tipo de transacao: Aplicacao\n");
                break;
            case RESG:
                printf("Tipo de transacao: Resgate\n");
                break;
            case PIX:
                printf("Tipo de transacao: Pix\n");
                break;
            case REND:
                printf("Tipo de transacao: Rendimento\n");
                break;
            case PIXR:
                printf("Tipo de transacao: Receber Pix\n");
                break;
        }
        printf("Valor da transacao: R$%.2f\n", minha_conta.log[i].valor / 100.0);
        printf("Saldo corrente apos: R$%.2f\n", minha_conta.log[i].saldo_corrente_apos / 100.0);
        printf("Saldo poupanca apos: R$%.2f\n", minha_conta.log[i].saldo_poupanca_apos / 100.0);
        if (minha_conta.log[i].tipo == PIX){
            printf("Destino do pix: %s\n", minha_conta.log[i].destino);
        }
        printf("%s\n", minha_conta.log[i].quando);
    }
} //imprime as transações realizadas e o saldo final.