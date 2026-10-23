#ifndef INVESTIMENTOS_H
#define INVESTIMENTOS_H


struct Acao {
    char   ticker[10];
    double preco;
    double lpa;          // lucro por acao 
    double dividendo;    //dividendo pago por acao em 12 meses 
};

struct Fundo {
    char   nome[30];
    double rentabilidade;  // nos ultimos 12 meses 
    double taxa_adm;       //% ao ano 
    double cdi;            // % do CDI nos ultimos 12 meses 
};

struct CDB {
    double valor;          // quanto vai aplicar (R$) 
    double percentual_cdi;  //ex: 110 
    double cdi;             //CDI anual (%) 
    int    dias;           // prazo em dias 
};


void ler_acao(struct Acao *a);
void analisar_acao(struct Acao *a);

void ler_fundo(struct Fundo *f);
void analisar_fundo(struct Fundo *f);

void ler_cdb(struct CDB *c);
void analisar_cdb(struct CDB *c);

#endif