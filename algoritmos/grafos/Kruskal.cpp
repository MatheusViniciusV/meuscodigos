//Objetivo: Busca uma árvore geradora mínima para um grafo conexo com pesos.
//Complexidade: O(A * logV)

struct Aresta {
    int origem, destino, peso;
    inline bool operator<(Aresta outra) { return peso < outra.peso; }
};

typedef vector<Aresta> Grafo;

Grafo original, AGM;
int* pai; //possui tamanho V e inicialmente cada vértice é o seu próprio pai (pai[i] = i)

int encontrar_conjunto(int i) {
    return (i != pai[i]) ? i = encontrar_conjunto(pai[i]) : i;
}

void unir_conjuntos(int u, int v) {
    pai[u] = pai[v];
}

void Kruskal() {
    
    Grafo copia = original;
    
    sort(copia.begin(), copia.end()); //ordena pelos pesos
    
    for (Aresta A : copia) {
        int conjunto_origem = encontrar_conjunto(A.origem);
        int conjunto_destino = encontrar_conjunto(A.destino);
        if (conjunto_origem != conjunto_destino) {
            AGM.push_back(A); 
            unir_conjuntos(conjunto_origem, conjunto_destino);
        }
    }
}
