#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//================================================================
// Nome Do Arquivo: primos.c
// Descrição: Gerador de números primos até um número N
//
// Matheus Vinicius, Informática, CEFET-MG
//================================================================

int main() {

    //Declaração de variáveis
    unsigned int nMax, i, j, verificacao;

    //Recebe o valor limite
    printf("Digite o limite superior para os numeros primos (minimo 2): ");
    scanf("%d", &nMax);
    while (nMax < 2) {
        system("clear");
        printf("Valor invalido\nDigite novamente o limite superior para os numeros primos (minimo 2): ");
        scanf("%d", &nMax);
    }

    //Primeiro valor a ser imprimido
    printf("2 ");

    //Verifica e imprime o número se é primo
    for (i = 3; i <= nMax; i = 2 + i) {
        
        //Eliminando os números pares
        if(i % 2) == 0)
            continue;

        //Cálculo e verificação
        verificacao = 1;
        for (j = 3; j <= (unsigned int)sqrt((float)i) + 1; j++) {
            if (i % j == 0) {
                verificacao = 0;
                break;
            }
        } 
        
        //Imprime o número na tela
        if (ehPrimo)
            printf("%d ", i);
    }

    return 0;
}