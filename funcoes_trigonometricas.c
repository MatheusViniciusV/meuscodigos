#include <math.h> //fmod

#define LIMITE 27 //Controla o número de polinômios nas aproximações

double rad(int graus) { //Conversão de graus para radianos
    return M_PI / 180 * graus; 
}

double seno(double x)  {
    
    x = fmod(x,M_PI*2); //Desconsidera as voltas inteiras no círculo trigonométrico
    
    double r = x, t = x;
 
    for(int i = 3; i < LIMITE; i += 2) //Série de Taylor na forma da função seno
        r += t = -t*x*x/(i*(i-1));   
    
    return r; 
}

double cosseno(double x)  { 
    
    x = fmod(x,M_PI*2);
    
    double r = 1, t = 1;
 
    for(int i = 2; i < LIMITE; i += 2) //Série de Taylor na forma da função cosseno
        r += t = -t*x*x/(i*(i-1));     
    
    return r;
}

double tangente(double x) {
    
    x = fmod(x,M_PI*2);
    
    double rsen = x, tsen = x;
    double rcos = 1, tcos = 1;
    
    for(int i = 2; i < LIMITE; i += 2) { //Cálculo do Seno e Cosseno
        rsen += tsen = -tsen*x*x/((i+1)*i);
        rcos += tcos = -tcos*x*x/(i*(i-1)); 
    }
    
    return rsen/rcos; //Identidade trigonométrica
}
