//Objetivo: Retorna um vetor dos fatores de um número N
//Complexidade (menor fator primo): O(sqrt(n))
//Complexidade (fatoração): O(log n * sqrt(n))

int menorFatorPrimo(int n) {
    for(int i = 2; i * i <= n; ++i)
        if(n % i == 0)
            return i;
    return n;
}

vector<int> fatorar(int n) {

    vector<int> fatores;
  
    while(n != 1) {
        int fator = menorFatorPrimo(n);
        fatores.push_back(fator);
        n /= fator;
    }

    return fatores;
}
