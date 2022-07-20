double delta(double a, double b, double c) {
    return b * b - 4 * a * c;
}

double x_vertice(double a, double b) {
    return -b / (2 * a);
}

double y_vertice(double a, double b, double c) {
    return delta(a, b, c) / (4 * a);
}

double x1(double a, double b, double c) {
    return (-b + sqrt(delta(a, b, c))) / (2 * a);
}

double x2(double a, double b, double c) {
    return (-b - sqrt(delta(a, b, c))) / (2 * a);
}

double x1_ax_c(double a, double c) {
    return sqrt(-c / a);
}

double x2_ax_c(double a, double c) {
    return -sqrt(-c / a);
}

int x1_ax_bx(double a, double b) {
    return 0;
}

double x2_ax_bx(double a, double b) {
    return -b / a;
}

int x_ax(double a) {
    return 0;
}

double valor_de_y(double a, double b, double c, double x) {
    double y = a * x * x + b * x + c;
    return y;
}
