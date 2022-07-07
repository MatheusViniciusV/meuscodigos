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
    printf("*********** ALGORITMO GERADOR DE NUMEROS PRIMOS ***********\n\n");
    printf("Digite o limite superior para os numeros primos (minimo 2): ");
    scanf("%d", &nMax);
    while (nMax < 2) {
        system("cls");
        printf("Valor invalido\nDigite novamente o limite superior para os numeros primos (minimo 2): ");
        scanf("%d", &nMax);
    }

    //Primeiras impressões
    system("cls");
    printf("*********** Lista de primos ate %d ***********\n\n", nMax);
    printf("2 ");

    //Verifica e imprime o número se é primo
    for(int i = 3; i <= nMax; i = 2 + i) {
        
        //Eliminando os múltiplos de 3
        if(i % 3 == 0 && i != 3)
            continue;

        //Cálculo e verificação
        verificacao = 1;
        for(int j = 3; j <= (unsigned int)sqrt((float)i)+1; j++) {
            if (i % j == 0) {
                verificacao = 0;
                break;
            }
        } 
        
        //Imprime o número na tela
        if (verificacao)
            printf("%d ", i);
    }

    //Finaliza o programa
    printf("\n\n");
    system("pause");

    return 0;
}
