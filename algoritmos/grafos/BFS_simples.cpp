int BFS(int A, int B)
{
    vector<int> distancia(T + L + 1, -1);
    queue<int> fila;

    fila.push(A);
    distancia[A] = 0;

    while (not fila.empty())
    {
        int atual = fila.front();
        fila.pop();

        for (int vizinho : adjacencias[atual])
        {
            if (distancia[vizinho] == -1)
            {
                distancia[vizinho] = distancia[atual] + 1;
                if(vizinho == B) return distancia[vizinho];
                fila.push(vizinho);
            }
        }
    }
    
    return -1;
}
