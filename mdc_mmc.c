int MDC(int a, int b) {

    int r;

    while (r != 0) {
        r = a % b;
        a = b;
        b = r;
    }
    
    return a;
}

int MMC(int a, int b) {
    
    int mmc, mdc = calcMDC(a, b);
    
    mmc = (a * b) / mdc;

    return mmc;    
}
