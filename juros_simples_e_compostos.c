double juros_simples(double C, double i, double t) {
    return C * i * t;
}

double montante_juros_simples(double C, double i, double t) {
    return C * (i * t + 1);
}

double juros_compostos(double C, double i, double t) {
    return C * (pow(1 + i, t) - 1);
}

double montante_juros_compostos(double C, double i, double t) {
    return C * pow(1 + i, t);
}
