long long int fatorial(int n, int r) {
    
    if(n != 0) return fatorial(n - 1, n * r);
    
    return r;
}

long long int fatorial(int n) {
    return fatorial(n, 1);
}
