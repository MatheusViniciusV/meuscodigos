void selectionSort (int *V, int n) {
  int menor;

  for (int i = 0; i < n - 1; i++) {
    menor = i;
    for (int j = i + 1; j < n; j++) {
      if (V[j] < V[menor]) {
        menor = j;
      }
    }

    if (i != menor) {
      int tmp = V[i];
      V[i] = V[menor];
      V[menor] = tmp; 
    }
  }
}
