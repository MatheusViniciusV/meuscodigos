vector<vector<int>> adj;

int bfs(int A, int B)
{
    vector<bool> vis(vertices, false);
    queue<pair<int, int>> fila;

    fila.push({A, 0});
    vis[A] = true;

    while (!fila.empty())
    {
        int atual = fila.front().first;
        int distancia = fila.front().second;
        fila.pop();

        if (atual == B)
            return distancia;

        for (int vizinho : adj[atual])
        {
            if (!vis[vizinho])
            {
                fila.push({vizinho, distancia + 1});
                vis[vizinho] = true;
            }
        }
    }
    
    return -1;
}
