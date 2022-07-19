int num_divisores(int n) {
    
    int c = 2;
    
    for(int i = 2; i < ((int)floor(sqrt(n)))+1; i++)
        if(n % i == 0)
            c += (n / i == i) ? 1 : 2;
            
    return c;
}
