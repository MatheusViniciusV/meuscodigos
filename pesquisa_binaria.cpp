int pesquisaBinaria(int arr[], int i, int f, int num) {
    
    if(i <= f) {
        
        int meio = (i + f) / 2;
        
        if(arr[meio] > num)
            return pesquisaBinaria(arr, i, meio - 1, num);
        if(arr[meio] < num)
            return pesquisaBinaria(arr, meio + 1, f, num);
        if(arr[meio] == num)
            return meio;
   }
   
   return -1;
}
