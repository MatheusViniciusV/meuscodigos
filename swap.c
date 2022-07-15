void simples_swap(int *a, int *b)
{
    long aux = *a;
    *a = *b;
    *b = aux;
}

void arit_swap(int *a, int *b)
{
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

void xor_swap(int *a, int *b)
{
    *b = *a ^ *b;
    *a = *a ^ *b;
    *b = *a ^ *b;
}
