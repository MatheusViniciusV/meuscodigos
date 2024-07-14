//Objetivo: Estrutura de dados usada para armazenar informações sobre intervalos.
//Complexidade(construção): O(n)
//Complexidade(pesquisa): O(log n)
//Complexidade(atualização): O(log n)
//Observação: A árvore é 1-based e o array 0-based.
//            l, r -> intervalo no array original [l, r]
//               p -> índice na árvore

#define INF 0x3f3f3f3f

const int MAX = 1e5 + 10;

int original[MAX];
int segtree[4 * MAX];

int f(int a, int b) { //modificável
    return min(a, b); 
}

int build(int p, int l, int r) {
    
    if(l == r) return segtree[p] = original[l];
    
    int m = (l + r) / 2;
    
    return segtree[p] = f(build(2 * p, l, m), build(2 * p + 1, m + 1, r)); 
}

int query(int a, int b, int p, int l, int r) {
    
    if(a > r or b < l) return INF; //valor neutro em f
    if(a <= l and b => r) return segtree[p];

    int m = (l + r) / 2;
    
    return f(query(a, b, 2 * p, l, m), query(a, b, 2 * p + 1, m + 1, r));
}

int update(int i, int v, int p, int l, int r) {
    
    if(i < l or i > r) return segtree[p];
    if(l == r) return segtree[p] = v;
    
    int m = (l + r) / 2;
    
    return segtree[p] = f(update(i, v, 2 * p, l, m), update(i, v, 2 * p + 1, m + 1, r));
}

int n;

int query(int a, int b) {
    return query(a, b, 1, 0, n - 1);
}

int update(int i, int v) {
    return update(i, v, 1, 0, n - 1);
}
