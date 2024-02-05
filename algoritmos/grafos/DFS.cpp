//Objetivo: Busca em um grafo todos os nós acessíveis partindo de um nó raiz
//Complexidade: O(V + A)

const int MAX = 1e3+10;

vector<bool> visitado(MAX, false);
vector<vector<int>> adjacencias(MAX);

void DFS(int vertice) {
    
    visitado[vertice] = true;
    
    for(auto vizinho : adjacencias[vertice])
        if(!visitado[vizinho]) DFS(vizinho);
}
