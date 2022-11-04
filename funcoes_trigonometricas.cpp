#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

#define ITERACOES 15
#define PI 3.14159265

double radianos(double graus);
double seno(double graus);
double cosseno(double graus);
double tangente(double graus);

int main() {
    
    double alfa;
    
    cout << "Digite um ângulo em graus para ser analisado: ";
    
    cin >> alfa;
    
    cout << endl;
    cout.setf(ios::left);
    cout << setw(12) << "Radianos: " << setw(12) << radianos(alfa) << endl;
    cout << setw(12) << "Seno: "     << setw(12) << seno(alfa)     << endl;
    cout << setw(12) << "Cosseno: "  << setw(12) << cosseno(alfa)  << endl;
    cout << setw(12) << "Tangente: " << setw(12) << tangente(alfa) << endl;

    return 0;
}

double radianos(double graus) {
    return (graus * PI) / 180;
}

double seno(double graus) {
    
    if(graus == 180 || graus == 360)
        return 0;
    if(graus == 90 || graus == 270)
        return 1;
    
    double x = radianos(graus);
    
    x = fmod(x, 2 * PI);
    
    if(x >= PI * 1.5)    return -seno(2 * PI - x);
    if(x >= PI * 1.0)    return -seno(x + PI);
    if(x >= PI * 0.5)    return seno(PI - x);
    
    double resultado = x;
    double termo = x;
    
    for(int i = 3; i < ITERACOES; i += 2) {
        termo = -termo * x * x / (i * (i - 1));
        resultado += termo;
    };
 
    return resultado; 
}

double cosseno(double graus) {
    
    if(graus == 180 || graus == 360)
        return 1;
    if(graus == 90 || graus == 270)
        return 0;
        
    return seno(90 - graus);
}

double tangente(double graus) {
    return seno(graus) / cosseno(graus);
}
