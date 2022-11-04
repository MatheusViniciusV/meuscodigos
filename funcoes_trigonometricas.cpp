#include <iostream> //cin cout
#include <cmath> //fmod
#include <iomanip> //setw

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
    
    //Desconsidera as voltas inteiras no círculo trigonométrico
    graus = fmod(graus, 360);
    
    if(graus == 0 || graus == 180)
        return 0;
    if(graus == 90 || graus == 270)
        return 1;
        
    //Redução ao primeiro quadrante
    if(graus > 270) return -seno(360 - graus);
    if(graus > 180) return -seno(graus - 180);
    if(graus > 90)  return  seno(180 - graus);
    
    //Conversão para radianos e início dos cálculos
    double x = radianos(graus);
    
    double resultado = x;
    double termo = x;
    
    //Cálculo da Série de Taylor na forma da função seno
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
    
    //Definição de cosseno em função do seno (ângulo complementar)
    return seno(90 - graus);
}

double tangente(double graus) {
    return seno(graus) / cosseno(graus); //Identidade trigonométrica
}
