int num_na_sequencia_de_fibonacci(unsigned int n) {
    
    int num = 1;
    
    for(n--; n != 0; n--)
        num = lround(num * 1.6);
    
    return num;
}
