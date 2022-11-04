#include <cmath> //fmod

//Controla o número de polinômios na aproximação
#define LIMIT 25

//Converte graus para radianos
double rad(int degrees) {
    return M_PI / 180 * degrees; 
}

//Corpo comum das funções seno e cosseno
double taylor(double x, int i, double bg)  { 
    
    x = fmod(x,M_PI*2); //Desconsidera as voltas inteiras no círculo trigonométrico
    
    double r = bg, t = bg;
 
    for(; i < LIMIT; i += 2) //Série de Taylor
        r += t = -t*x*x/(i*(i-1));         
 
    return r; 
}

double sin(double x)  { 
    return taylor(x, 3, x); 
}

double cos(double x)  { 
    return taylor(x, 2, 1);
}

double tan(double x) {
    return sin(x)/cos(x); //Identidade trigonométrica
}
