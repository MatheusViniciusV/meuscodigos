//Objetivo: Busca um caminho em que o cavalo passe por todo tabuleiro sem repetir casas
//Complexidade: Não é eficiente, serve apenas de exemplo de algoritmo backtracking

#include <bits/stdc++.h>

using namespace std;

#define N 7
#define i_inicial 0
#define j_inicial 0

vector<pair<int, int>> movimentos = {{1,  2}, {1,  -2},
                                     {2,  1}, {2,  -1},
                                     {-1, 2}, {-1, -2},
                                     {-2, 1}, {-2, -1}};
                                     
vector<vector<int>> tabuleiro(N, vector<int>(N, -1));

bool posicao_valida(int i, int j) {
    return i >= 0 and i < N and j >= 0 and j < N and tabuleiro[i][j] == -1;
}

bool passeio_do_cavalo(int i, int j, int cont_passos) {
    
    if(cont_passos == N * N) return true;
    
    for(auto movimento : movimentos) {
        
        int proximo_i = i + movimento.first;
        int proximo_j = j + movimento.second;
        
        if(posicao_valida(proximo_i, proximo_j)) {
            //backtracking
            tabuleiro[proximo_i][proximo_j] = cont_passos;
            if(passeio_do_cavalo(proximo_i, proximo_j, cont_passos + 1)) return true;
            tabuleiro[proximo_i][proximo_j] = -1; 
        }
    }
    
    return false;
}

int main() {
    
    tabuleiro[i_inicial][j_inicial] = 0;
    
    if(passeio_do_cavalo(i_inicial, j_inicial, 1)) {
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                printf("%d\t", tabuleiro[i][j]);
            }
            printf("\n");
        }
    } else {
        cout << "Solução não encontrada" << endl;
    }
    
    return 0;
}
