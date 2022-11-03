bool verificacao_primo (unsigned int n) {
    
    if (n == 2) return true;
    if (n < 2 || n % 2 == 0) return false;

    for(int i = 3; i <= (unsigned int)sqrt((double)n)+1; i += 2) {
        if (n % i == 0) 
            return false;
    } 
    
    return true;
}

int prox_primo (unsigned int k) {
    
    k++;
    
    while(verificacao_primo(k) ==  false)
        k++;
    
    return k;
}
