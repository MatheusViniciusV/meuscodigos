//Objetivo: Constrói uma árvore implícita que eficientemente atualiza e consulta soma de prefixos
//Complexidade (construção): O(n)
//Complexidade (atualização): O(log n)
//Complexidade (pesquisa): O(log n)
//Obs: A árvore é 1-based

vector<int> fenwick;

void construct(vector<int> arr) {
    fenwick.resize(arr.size() + 1);
    for(int i = 1; i < fenwick.size(); i++) {
        fenwick[i] += arr[i - 1]; 
        int j = i + (i & -i);
        if(j < fenwick.size()) fenwick[j] += fenwick[i]; 
    }
}

void update(int i, int v) {
    while(i < fenwick.size()) {
        fenwick[i] += v;
        i += (i & -i);
    }
}

int query(int i) {
    int v = 0;
    while(i > 0) {
        v += fenwick[i];
        i -= (i & -i);
    }
    return v;
}
