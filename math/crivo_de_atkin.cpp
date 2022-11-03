vector<int> CrivoDeAtkin(int limite) {
    
    vector<int> primos;
    bool tabela[limite]{};
    
    if(limite > 2) tabela[2] = true;
    if(limite > 3) tabela[3] = true;
    for(int a = 1; a * a < limite; a++)
        for(int b = 1; b * b < limite; b++) {
            int n = (4 * a* a) + (b * b);
            if(n <= limite && (n % 12 == 1 || n % 12 == 5))
                tabela[n] ^= true;
            n = (3 * a * a) + (b * b);
            if(n <= limite && n % 12 == 7)
            tabela[n] ^= true;
            n = (3 * a * a) - (b * b);
            if(a > b && n <= limite && n % 12 == 11)
                tabela[n] ^= true;
        }
    for(int r = 5; r * r < limite; r++)
        if(tabela[r])
            for(int i = r * r; i < limite; i += r * r)
                tabela[i] = false;
    
    for(int x = 2; x < limite; x++)
        if(tabela[x])
            primos.push_back(x);
        
    return primos;
}
