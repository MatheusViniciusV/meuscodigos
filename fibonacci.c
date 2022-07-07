#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//================================================================
// Nome Do Arquivo: fibonacci.c
// Descrição: Gera a Sequência de Fibonacci até um número N
//
// Matheus Vinicius, Informática, CEFET-MG
//================================================================

int main()
{
    //Declaração de variáveis
    int nMAX;
    long long int num = 1;

    /*
    Parte mais importante do código, o Número de Ouro ou Razão Áurea é a
    razão entre dois números na Sequência de Fibonacci e/ou a razão entre dois
    números que cumprem a proporção (a + b) / a = a / b. Resolvendo a equação 
    algébrica anterior, é possível calcular este número como (1 + sqrt(5)) / 2.
    */ const double razaoaurea = 1.6180339887;
    
    //Leitura do número máximo
    printf("*********** ALGORITMO GERADOR DA SEQUENCIA DE FIBONACCI ***********\n\n");
    printf("Digite a quantidade de numeros para a Sequencia de Fibonacci: ");
    scanf("%d", &nMAX);
    
    //Primeiro valor imprimido
    system("cls");
    printf("*********** %d primeiros numeros da Sequencia de Fibonacci ***********\n\n", nMAX);
    printf("1 ");

    //Imprimir a Sequência de Fibonacci até o número máximo
    for(int i = 1; i <= nMAX; i++) {

        //Impressão do número na tela
        printf("%lld ", num);

        //Cálculo do número com a razão áurea e arredondamento para o inteiro mais próximo
        num = round(num * razaoaurea);
    }

    //Finaliza o programa
    printf("\n\n");
    system("pause");

    return 0;
}
