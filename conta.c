#include <stdio.h>
#include "conta.h"
#include <string.h>
#include <time.h>
#include <math.h>

static Conta usuario;

void data_horario(char datahorario[], int tamanho) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    strftime(datahorario, tamanho, "%Y-%m-%d %H:%M:%S", tm);
}

void conta_init(void){
    usuario.saldo_corrente = 0;
    usuario.saldo_poupanca = 0;
    usuario.nlog = 0;
}

int depositar(long long valor){
    if (valor <= 0){
        return ERRO_VALOR_INVALIDO;
    }

    if (usuario.nlog >= MAX_TRANS){
        return ERRO_CAPACIDADE_LOG;
    }
    usuario.saldo_corrente += valor;
    usuario.log[usuario.nlog].tipo = DEP;
    usuario.log[usuario.nlog].valor = valor;
    usuario.log[usuario.nlog].saldo_corrente_apos = usuario.saldo_corrente;
    usuario.log[usuario.nlog].saldo_poupanca_apos = usuario.saldo_poupanca;
    data_horario(usuario.log[usuario.nlog].quando, 20);
    usuario.nlog ++;
    return OK;
}

int sacar(long long valor){
    if (valor <= 0){
        return ERRO_VALOR_INVALIDO;
    }

    if (valor > usuario.saldo_corrente){
        return ERRO_SALDO_INSUFICIENTE;
    }

    if (usuario.nlog >= MAX_TRANS){
        return ERRO_CAPACIDADE_LOG;
    }

    usuario.saldo_corrente -= valor;
    usuario.log[usuario.nlog].tipo = SAQ;
    usuario.log[usuario.nlog].valor = valor;
    usuario.log[usuario.nlog].saldo_corrente_apos = usuario.saldo_corrente;
    usuario.log[usuario.nlog].saldo_poupanca_apos = usuario.saldo_poupanca;
    data_horario(usuario.log[usuario.nlog].quando, 20);
    usuario.nlog ++;

    return OK;
}

int aplicar_poupanca(long long valor){
    if (valor <= 0){
        return ERRO_VALOR_INVALIDO;
    }

    if (valor > usuario.saldo_corrente){
        return ERRO_SALDO_INSUFICIENTE;
    }

    if (usuario.nlog >= MAX_TRANS){
        return ERRO_CAPACIDADE_LOG;
    }
    usuario.saldo_corrente -= valor;
    usuario.saldo_poupanca += valor;
    usuario.log[usuario.nlog].tipo = APLI;
    usuario.log[usuario.nlog].valor = valor;
    usuario.log[usuario.nlog].saldo_corrente_apos = usuario.saldo_corrente;
    usuario.log[usuario.nlog].saldo_poupanca_apos = usuario.saldo_poupanca;
    data_horario(usuario.log[usuario.nlog].quando, 20);
    usuario.nlog ++;

    return OK;
} // passar dinheiro da conta para a poupanca

int resgatar_poupanca(long long valor){
    if (valor <= 0){
        return ERRO_VALOR_INVALIDO;
    }

    if (valor > usuario.saldo_poupanca){
        return ERRO_SALDO_INSUFICIENTE;
    }

    if (usuario.nlog >= MAX_TRANS){
        return ERRO_CAPACIDADE_LOG;
    }
    usuario.saldo_corrente += valor;
    usuario.saldo_poupanca -= valor;
    usuario.log[usuario.nlog].tipo = RESG;
    usuario.log[usuario.nlog].valor = valor;
    usuario.log[usuario.nlog].saldo_corrente_apos = usuario.saldo_corrente;
    usuario.log[usuario.nlog].saldo_poupanca_apos = usuario.saldo_poupanca;
    data_horario(usuario.log[usuario.nlog].quando, 20);
    usuario.nlog ++;
    return OK;
} //passar dinheiro da poupanca para a conta

int fazer_pix(const char destino[], long long valor){
    if (valor <= 0){
        return ERRO_VALOR_INVALIDO;
    }

    if (valor > usuario.saldo_corrente){
        return ERRO_SALDO_INSUFICIENTE;
    }

    if (usuario.nlog >= MAX_TRANS){
        return ERRO_CAPACIDADE_LOG;
    }
    usuario.saldo_corrente -= valor;
    usuario.log[usuario.nlog].tipo = PIX;
    usuario.log[usuario.nlog].valor = valor;
    usuario.log[usuario.nlog].saldo_corrente_apos = usuario.saldo_corrente;
    usuario.log[usuario.nlog].saldo_poupanca_apos = usuario.saldo_poupanca;
    strncpy(usuario.log[usuario.nlog].destino, destino, 127);
    usuario.log[usuario.nlog].destino[127] = '\0';
    data_horario(usuario.log[usuario.nlog].quando, 20);
    usuario.nlog ++;
    return OK;
} //tirar dinheiro da conta e transferir para a chave pix



long long saldo_corrente(void){
    return usuario.saldo_corrente;
} //retorna o valor do saldo corrente

long long saldo_poupanca(void){
    return usuario.saldo_poupanca;
} //retorna o valor da poupança

void extrato_imprimir(void){
    for (int i = 0; i < usuario.nlog; i++){
        printf("\nTransacao #%d\n", i + 1);
        switch (usuario.log[i].tipo){
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
        printf("Valor da transacao: R$%.2f\n", usuario.log[i].valor / 100.0);
        printf("Saldo corrente apos: R$%.2f\n", usuario.log[i].saldo_corrente_apos / 100.0);
        printf("Saldo poupanca apos: R$%.2f\n", usuario.log[i].saldo_poupanca_apos / 100.0);
        if (usuario.log[i].tipo == PIX){
            printf("Destino do pix: %s\n", usuario.log[i].destino);
        }
        printf("%s\n", usuario.log[i].quando);
    }
} //imprime as transações realizadas e o saldo final.