void bubble_sort (int *V, int n) {
  bool troca;

  do {
    troca = false;

    for (int i = 0; i < n - 1; i++) {
      if (V[i] > V[i + 1]) {
        int temp = V[i];
        V[i] = V[i + 1];
        V[i + 1] = temp;
        troca = true;
      }
    }
  } while (troca);
}
