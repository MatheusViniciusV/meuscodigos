//Objetivo: Busca o menor caminho entre dois vértices de um grafo conexo ponderado sem pesos negativos
//Complexidade: O(A + VlogV)

#include <iostream>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f

using namespace std;

int numero_vertices; 
vector<vector<pair<int, int>>> adjacencias; //pair<vertice, distancia>

int dijkstra(int origem, int destino)
{
  vector<int> distancia(numero_vertices, INF);
  vector<bool> visitado(numero_vertices, false);

  //pair<distancia, vertice>
	priority_queue<pair<int, int>> fila;
	
	distancia[origem] = 0;
	fila.push({distancia[origem], origem});

	while(not fila.empty()) {
	    
		pair<int, int> topo = fila.top();
		int vertice_atual = topo.second;
		fila.pop();

		if(not visitado[vertice_atual]) {
		    
			visitado[vertice_atual] = true;
			
			for(auto adjacencia : adjacencias[vertice_atual]) {
			    
			  int vertice_vizinho = adjacencia.first;
				int custo_aresta = adjacencia.second;

				if(distancia[vertice_vizinho] > (distancia[vertice_atual] + custo_aresta))
				{
					distancia[vertice_vizinho] = distancia[vertice_atual] + custo_aresta;
					fila.push({distancia[vertice_vizinho], vertice_vizinho});
				}
			}
		}
	}

	return distancia[destino];
}

int main()
{
    numero_vertices = 5;
    adjacencias.resize(numero_vertices);

	  adjacencias[0].push_back({1, 4});
	  adjacencias[0].push_back({2, 2});
	  adjacencias[0].push_back({3, 5});
    adjacencias[1].push_back({4, 1});
    adjacencias[2].push_back({1, 1});
    adjacencias[2].push_back({3, 2});
    adjacencias[2].push_back({4, 1});
    adjacencias[3].push_back({4, 1});

	  cout << dijkstra(0, 4) << endl;

	return 0;
}
