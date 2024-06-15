//UNIÃO
//Objetivo: Une dois elementos em um conjunto
//Complexidade: O(1)

//ENCONTRA
//Objetivo: Busca qual o conjunto que o elemento pertence
//Complexidade: O(logN)

int pai[MAX]; //inicialmente com todo pai[i] = i

void unir(a, b) { pai[a] = b; }
int encontra(int n) { return pai[n] == n ? n : pai[n] = encontra(pai[n]); }
