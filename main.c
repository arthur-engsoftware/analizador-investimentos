#include <stdio.h>
#include "investimentos.h"

int main(void)
{
    int opcao;

    do {
        printf("\n===== ANALISADOR DE INVESTIMENTOS =====\n");
        printf("1 - Acao\n");
        printf("2 - Fundo\n");
        printf("3 - CDB\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1: {
            struct Acao a;           //cria a ficha 
            ler_acao(&a);            //&a = endereco da ficha (ponteiro) 
            analisar_acao(&a);
            break;
        }
        case 2: {
            struct Fundo f;
            ler_fundo(&f);
            analisar_fundo(&f);
            break;
        }
        case 3: {
            struct CDB c;
            ler_cdb(&c);
            analisar_cdb(&c);
            break;
        }
        case 0:
            printf("Ate mais!\n");
            break;
        default:
            printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}