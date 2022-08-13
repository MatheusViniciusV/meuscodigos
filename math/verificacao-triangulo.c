bool v(int a, int b, int c) {
    return abs(b - c) < a && a < b + c && abs(a - c) < b && b < a + c && abs(a - b) < c && c < a + b;
}
