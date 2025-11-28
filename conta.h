#ifndef CONTA_H
#define CONTA_H

#define MAX_TRANS 100

typedef enum { DEP, SAQ, APLI, RESG, PIX, REND, PIXR } TipoTransacao;

typedef struct {
    TipoTransacao tipo;
    long long valor;
    long long saldo_corrente_apos;
    long long saldo_poupanca_apos;
    char destino[128];
    char quando[20];
} Transacao;

typedef struct {
    long long saldo_corrente;
    long long saldo_poupanca;
    Transacao log[MAX_TRANS];
    int nlog;
} Conta;

enum {
    OK = 0,
    ERRO_VALOR_INVALIDO = 1,
    ERRO_SALDO_INSUFICIENTE = 2,
    ERRO_CAPACIDADE_LOG = 3
};

extern Conta minha_conta;

void conta_init(void);
int  depositar(long long valor);
int  sacar(long long valor);
int  aplicar_poupanca(long long valor);
int  resgatar_poupanca(long long valor);
int  fazer_pix(const char destino[], long long valor);
long long saldo_corrente(void);
long long saldo_poupanca(void);
void extrato_imprimir(void);

#endif // CONTA_H
