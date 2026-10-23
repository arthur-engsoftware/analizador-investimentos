#include <stdio.h>
#include <math.h>
#include "investimentos.h"

/* Resultado final, igual para os tres tipos */
static void mostrar_resultado(int pontos, int total)
{
    printf("\nCriterios atendidos: %d de %d\n", pontos, total);
    if (pontos == total)
        printf("RESULTADO: BOA OPCAO\n");
    else if (pontos > 0)
        printf("RESULTADO: REGULAR\n");
    else
        printf("RESULTADO: OPCAO FRACA\n");
}


void ler_acao(struct Acao *a)
{
    printf("Ticker: ");
    scanf("%9s", a->ticker);
    printf("Preco atual (R$): ");
    scanf("%lf", &a->preco);
    printf("Lucro por acao em 12 meses (R$): ");
    scanf("%lf", &a->lpa);
    printf("Dividendo por acao em 12 meses (R$): ");
    scanf("%lf", &a->dividendo);
}

void analisar_acao(struct Acao *a)
{
    int pontos = 0;
    double pl = 0;
    double dy = a->dividendo / a->preco * 100;   /* dividend yield (%) */

    printf("\n--- Analise de %s ---\n", a->ticker);

    if (a->lpa > 0) {
        pl = a->preco / a->lpa;                  /* preco / lucro */
        printf("P/L: %.2f (bom ate 15)\n", pl);
        if (pl <= 15) pontos++;
    } else {
        printf("Empresa com prejuizo, P/L nao se aplica.\n");
    }

    printf("Dividend Yield: %.2f%% (bom a partir de 6%%)\n", dy);
    if (dy >= 6) pontos++;

    mostrar_resultado(pontos, 2);
}


void ler_fundo(struct Fundo *f)
{
    printf("Nome do fundo: ");
    scanf("%29s", f->nome);
    printf("Rentabilidade em 12 meses (%%): ");
    scanf("%lf", &f->rentabilidade);
    printf("Taxa de administracao (%% ao ano): ");
    scanf("%lf", &f->taxa_adm);
    printf("CDI acumulado em 12 meses (%%): ");
    scanf("%lf", &f->cdi);
}

void analisar_fundo(struct Fundo *f)
{
    int pontos = 0;
    double liquida = f->rentabilidade - f->taxa_adm;

    printf("\n--- Analise do fundo %s ---\n", f->nome);

    printf("Rentabilidade liquida: %.2f%% (CDI: %.2f%%)\n", liquida, f->cdi);
    if (liquida >= f->cdi) pontos++;

    printf("Taxa de administracao: %.2f%% (boa ate 1.5%%)\n", f->taxa_adm);
    if (f->taxa_adm <= 1.5) pontos++;

    mostrar_resultado(pontos, 2);
}



void ler_cdb(struct CDB *c)
{
    printf("Valor a aplicar (R$): ");
    scanf("%lf", &c->valor);
    printf("Taxa do CDB (%% do CDI, ex: 110): ");
    scanf("%lf", &c->percentual_cdi);
    printf("CDI anual atual (%%): ");
    scanf("%lf", &c->cdi);
    printf("Prazo (dias): ");
    scanf("%d", &c->dias);
}

void analisar_cdb(struct CDB *c)
{
    int pontos = 0;
    double taxa = c->cdi * c->percentual_cdi / 100;  // taxa anual do CDB 
    double bruto = c->valor * (pow(1 + taxa / 100, c->dias / 365.0) - 1);
    double aliquota_ir;
    double liquido;
    double poupanca = c->valor * (pow(1.0617, c->dias / 365.0) - 1);

    //Imposto de Renda: quanto maior o prazo, menor a aliquota 
    if (c->dias <= 180)      aliquota_ir = 22.5;
    else if (c->dias <= 360) aliquota_ir = 20.0;
    else if (c->dias <= 720) aliquota_ir = 17.5;
    else                     aliquota_ir = 15.0;

    liquido = bruto - bruto * aliquota_ir / 100;

    printf("\n--- Analise do CDB ---\n");
    printf("Rendimento bruto:   R$ %.2f\n", bruto);
    printf("IR (%.1f%%):         R$ %.2f\n", aliquota_ir, bruto * aliquota_ir / 100);
    printf("Rendimento liquido: R$ %.2f\n", liquido);
    printf("Poupanca renderia:  R$ %.2f\n", poupanca);

    if (c->percentual_cdi >= 100) pontos++;
    if (liquido > poupanca) pontos++;

    mostrar_resultado(pontos, 2);
}