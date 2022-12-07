# DETERMINANTE EM UMA MATRIZ QUADRADA

---

## Explicação

Existem três operações básicas que podem ser aplicadas a
qualquer tipo de sistema linear, sem alterar sua solução:

1. Trocar duas linhas entre si.
2. Multiplicar todos os elementos de
uma linha por uma constante não-nula.
3. Substituir uma linha pela sua soma
com um múltiplo de outra.
    
Usando estas operações, uma matriz quadrada sempre pode
ser transformada numa matriz de forma escalonada, em que
será possível calcular seu determinante pelo produto dos
elementos da diagonal principal.

## Exemplo:

    Matriz de entrada:
        a    b    c
        d    e    f
        g    h    i
            
    Matriz escalonada:
        a    b    c
        0    e'   f'
        0    0    i''
            
    Cálculo do determinante:
        det = a * e' * i''
        
<i>Observação: Todos os elementos da diagonal são não-nulos.</i>

## Glossário:

Em álgebra linear, a diagonal principal de uma matriz A
é a coleção das entradas Aᵢⱼ em que i é igual a j.

Dizemos que uma matriz está escalonada quando:
    
1. As linhas que contém apenas zeros estão abaixo das demais.
2. O primeiro elemento não nulo de uma linha, conhecido como elemento líder,
está em uma coluna à direita do elemento líder da linha acima.

### double det(double **mat, int N)
Recebe como parâmetro uma matriz quadrada, e o seu tamanho. <br>
Não altera a matriz original passada para a função. <br>
Realiza o escalonamento da matriz e o cálculo do determinante. <br>
Retorna o determinante se foi possível calcular. <br>
Retorna CODIGO_DE_ERRO se não foi possível.
