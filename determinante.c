#define CODIGO_DE_ERRO 3.141592653

double det(double **mat, int N) {
    
    double A[N][N];
    double det = 1;
    int j, i, k;
    double R;
    
    //Criando cópia da matriz passada por referência
    for(i = 0; i < N; i++)
        for(j = 0; j < N; j++)
            A[i][j] = mat[i][j];
    
    //Escalonamento da matriz
    for(i = 0; i < N; i++) {
        
        if(A[i][i] == 0) return CODIGO_DE_ERRO;
        
		for(j = i + 1; j < N; j++) {
		    
	        R = A[j][i] / A[i][i];
	        
	         /*
		    Seja L uma linha na matriz, é
		    realizada a seguinte operação linear:
		    
		        Lj = Lj = R * Li;
		    */
	   
			for(k = 0; k < N; k++)
			  	A[j][k] = A[j][k] - R * A[i][k];
		}
    }

    //Cálculo do determinante
    for(i = 0; i < N; i++)
        det = det * A[i][i];
        
    return det;
}
