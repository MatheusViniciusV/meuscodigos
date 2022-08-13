int maiorAB(int a, int b) {
    return (a + b + abs(a - b)) / 2;
}

int maiorABC(int a, int b, int c) {
    return (2 * c + a + b + abs(a - b) + abs(-2 * c + a + b + abs(a - b))) / 4;
}
