//Objetivo: Busca o menor caminho entre dois vértices de um grafo conexo ponderado sem pesos negativos
//Complexidade: O(A + VlogV)

const int INF = 0x3f3f3f3f;

int dijkstra(vector<vector<pair<int, int>>>& grafo, int n, int origem, int destino) {
    
    vector<int> distancia(n, INF);
    vector<bool> visitado(n, false);
    
    priority_queue<pair<int, int>> fila;
    
    distancia[origem] = 0;
    fila.push({-distancia[origem], origem});
    
    while(not fila.empty()) {
        
        pair<int, int> topo = fila.top();
        int atual = topo.second;
        fila.pop();
        
        if(not visitado[atual]) {
            
            visitado[atual] = true;
            
            for(auto adjacencia : grafo[atual]) {
                
                int vizinho = adjacencia.first;
                int custo = adjacencia.second;
                
                if(distancia[vizinho] > (distancia[atual] + custo)) {
			distancia[vizinho] = distancia[atual] + custo;
			fila.push({-distancia[vizinho], vizinho});
		}
            }
        }
    }
    
    return distancia[destino];
}
