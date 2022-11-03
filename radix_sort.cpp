//#include <list>
//#include <cmath>

void radixSort(int arr[], int n, int digitos) {

    int m, p;
   
    list<int> bucket[10];
   
    for(int i = 0; i < digitos; i++) {
       
        m = pow(10, i + 1);
        p = pow(10, i);
      
        for(int j = 0; j < n; j++)
            bucket[(arr[j] % m) / p].push_back(arr[j]);
        
        for(int j = 0, cont = 0; j < 10; j++) {
            while(!bucket[j].empty()) {
                arr[cont] = *(bucket[j].begin());
                bucket[j].erase(bucket[j].begin());
                cont++;
            }
        }
    }
}
