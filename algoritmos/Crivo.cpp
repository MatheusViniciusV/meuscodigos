//Objetivo: Busca o todos os primos até N
//Complexidade: O(N log log N)

vector<bool> vefPrimo(MAX, true); //o vector deve ter no mínimo tamanho N+1

void crivoDeEratostenes(unsigned N) {
   for (unsigned p = 2; p * p <=N; ++p)
       if (vefPrimo[p])
           for (unsigned i = p * p; i <= N; i += p)
               vefPrimo[i] = false;
}
