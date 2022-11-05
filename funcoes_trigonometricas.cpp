#include <cmath> //fmod

#define LIMIT 30 //Controla o número de polinômios na aproximação

//Cálculo semelhante das funções seno e cosseno
double taylor(double x, int i, double bg)  { 
    
    double r = bg, t = bg;
 
    for(; i < LIMIT; i += 2) //Série de Taylor
        r += t = -t*x*x/(i*(i-1));         
 
    return r; 
}

double seno(double x)  {
    x = fmod(x,M_PI*2); //Desconsidera as voltas inteiras no círculo trigonométrico
    return taylor(x, 3, x); 
}

double cosseno(double x)  { 
    x = fmod(x,M_PI*2);
    return taylor(x, 2, 1);
}

double tangente(double x) {
    return sin(x)/cos(x); //Identidade trigonométrica
}
