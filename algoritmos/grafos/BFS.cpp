//Objetivo: Busca o menor caminho entre dois vértices de um grafo conexo não-ponderado
//Complexidade: O(V + A)

const int MAX = 1e3 + 10;

vector<bool> visitado(MAX, false);
vector<vector<int>> adjacencias(MAX);
vector<int> distancia(MAX, -1);
vector<int> pai(MAX, -1);

void BFS(int vertice) {
    
    queue<int> fila;
    
    fila.push(vertice);
    visitado[vertice] = true;
    distancia[vertice] = 0, pai[vertice] = vertice;
    
    while (!fila.empty()) { //enquanto ainda houver vertice à ser analisado
        
	    int vertice_atual = fila.front();
	    fila.pop();
	    
	    for (auto vizinho : adjacencias[vertice_atual]) if (!visitado[vizinho]) {
	        fila.push(vizinho); //adicionar vizinho na fila para ser analisado posteriormente
	        visitado[vizinho] = true;
	        distancia[vizinho] = distancia[vertice_atual] + 1;
	        pai[vizinho] = vertice_atual;
	  }
	}
}

vector<int> recuperar_caminho(int s) {
    
    vector<int> caminho;
    
    while(pai[s] != -1) {
        
        caminho.push_back(s);
        
        if(s == pai[s]) break;
        else s = pai[s];
    }
    
    reverse(caminho.begin(), caminho.end());
    
    return caminho;
}
