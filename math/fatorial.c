long long int fatorial(int n) {
    
    if(n != 0)
        return n * fatorial(n - 1);
    
    return 1;
}
