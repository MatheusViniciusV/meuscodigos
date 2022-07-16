void insertion_sort(int *V, int n) {
  int atual, j;

  for (int i = 1; i < n; i++) {
    atual = V[i];
    for (j = i; (j > 0) && (atual < V[j - 1]); j--) {
      V[j] = V[j - 1];
    }

    V[j] = atual;
  }
}
