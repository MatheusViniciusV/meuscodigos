//Objetivo: Dado o peso de objetos e seus valores, preencher a mochila com o maior
//valor possível, não ultrapassando o peso máximo.
//Complexidade: O(N * W)

int mochila(int W, int n) {
    
    vector<vector<int>> K(n + 1, vector<int>(W + 1));
    
    for(int i = 0; i <= n; i++) {
        for(int w = 0; w <= W; w++) {
            if(i == 0 || w == 0)
                K[i][w] = 0;
            else if(peso[i - 1] <= w)
                K[i][w] = max(valor[i - 1] + K[i - 1][w - peso[i - 1]], K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }
    
    return K[n][W];
}
