int encrypt_XOR_int(int a, int b) {
    return a ^ b;
}

void encrypt_XOR_string(char *array, int senha) {
    for(int i = 0; array[i] != '\0'; i++)
        array[i] ^= senha;
}
