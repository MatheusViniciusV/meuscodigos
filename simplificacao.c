#include <stdio.h>
#include <stdlib.h>

//================================================================
// Nome Do Arquivo: simplificacao.c
// Descrição: Algoritmo de simplificação de frações
//
// Matheus Vinicius, Informática, CEFET-MG
//================================================================

int calcMDC(int a, int b) {

    //Função que calcula MDC entre dois números

    int resto;

    while (resto != 0) {

        //Algoritmo de Euclides: Divisões sucessivas até que o resto seja zero.
        resto = a % b;
        a = b;
        b = resto;
    }
    
    //Retorna o valor do MDC após os cálculos
    return a;
}

int main() {

    //Declaração de variáveis
    int a, b, mdc;

    //Leitura de variáveis e interface do programa
    printf("*********** ALGORITMO DE SIMPLIFICACAO DE FRACOES ***********\n\n");
    printf("Informe o numerador de uma fracao para ser simplificada: ");
    scanf("%d", &a);
    system("cls");
    printf("*********** ALGORITMO DE SIMPLIFICACAO DE FRACOES ***********\n\n");
    printf("Informe o denominador de uma fracao para ser simplificada: %d / ", a);
    scanf("%d", &b);
    system("cls");

    //Cálculo e impressão do resultado
    printf("*********** Fracao %d / %d simplificada ***********\n\n", a, b);

    mdc = calcMDC(a, b);
    a /= mdc, b /= mdc;

    printf("%d / %d", a, b);

    //Finaliza o programa
    printf("\n\n");
    system("pause");

    return 0;
}