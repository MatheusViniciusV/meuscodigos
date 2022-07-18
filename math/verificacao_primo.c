int verificacao_primo (unsigned int n) {
    
    if (n == 2) return 1;
    if (n < 2 || n % 2 == 0) return 0;

    for(int i = 3; i <= (unsigned int)sqrt((double)n)+1; i += 2) {
        if (n % i == 0) 
            return 0;
    } 
    
    return 1;
}
