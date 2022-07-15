int calcMDC(int a, int b) {

    int resto;

    while (resto != 0) {
        resto = a % b;
        a = b;
        b = resto;
    }
    
    return a;
}
