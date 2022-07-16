#define swap(a, b) do{int tmp = a; a = b; b = tmp;}while(0)

const char * dec2bin(char * bin, int d) {

    int i = 0;
    int j = 0;

    for( i = 0; d > 0; d /= 2, i++)
        bin[i] = (d % 2) ? '1' : '0';

    for( j = 0; j < (i / 2); j++)
        swap(bin[j], bin[i - j - 1]);

    bin[i] = '\0';

    return bin;
}

int bin2dec( const char * bin ) {

    int n = 0;
    int i = 0;
    int nbits = strlen(bin);

    for( i = 0; i < nbits; i++ )
        n += (bin[ nbits - i - 1 ] == '1' ) ? (1 << i) : 0;

    return n;
}
