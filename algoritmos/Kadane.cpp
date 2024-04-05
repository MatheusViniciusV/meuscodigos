//Objetivo: Busca a maior soma contígua em um array
//Complexidade: O(N)

#define INF = 0x3f3f3f3f;

vector<int> arr;

int kadane() {
  int max_soma = -INF;
  int soma = 0;

  for(auto e : arr) {
    soma += e;
    max_soma = max(max_soma, soma);
    soma = max(soma, 0);
  }

  return max_soma;
}
