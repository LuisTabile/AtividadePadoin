#include <stdio.h>
#include <time.h>
#include <stdlib.h>   
#include "tempo.h"
#include <omp.h>

#define L 1000
#define C L
#define P L

double cubo[C][L][P]; //Criada nova dimensão 3D
double cubonew[C][L][P]; //Criada nova dimensão 3D

void inicializa_cubo();
void mostra_cubo();
void jacobi();
void mostra_cubo();

int main(int argc, char *argv[])
{

	char *argThreads = argv[1];

	int threads = atoi(argThreads);
	int qtdVezes = 5;

	printf("\nCalculando jacobi %d vezes, usando %d threads\n", qtdVezes, threads);

	inicializa_cubo();

	//mostra_cubo();

	tempo1();

	for (int z=0; z < qtdVezes; z ++){
		jacobi(threads);
		//mostra_cubo();
	}

	//mostra_cubo();

	tempo2();

	tempoFinal("mili segundos", argv[0], MSGLOG);


}

void mostra_cubo()
{
	int z, v, x;
        printf("\n  C U B O \n");

        for (z=0; z < L; z ++){
			for (v=0; v < C; v++) {
				for (x=0; x < P; x++){ //Criado novo (for) para mostrar o cubo
        	        printf(" %.3f", cubo[z][v][x]);
			}
			printf("\n");
		}
		printf("\n");
	}
	printf("\n\n\n");
	
}

void inicializa_cubo()
{
	srandom(time(NULL));
        int z, v, x;
        for (z=0; z < L; z ++)
			for (v=0; v < C; v++)
				for (x=0; x < P; x++)
					cubo[z][v][x] = 21.0;

        for (z=0; z < L; z ++)
			for (v=0; v < C; v++){
//lado esquerdo
					cubo[z][v][0] = 40.0;
//lado direito
 					cubo[z][v][P-1] = 40.0;
//cima
					cubo[0][v][z] = 40.0;
//baixo
 					cubo[L-1][v][z] = 40.0;
//frente
					cubo[v][0][z] = 40.0;
//atras
 					cubo[v][L-1][z] = 40.0;
			}
}

void jacobi(int threads)
{	
	int i, j, k;
	float divBy = (1.0/6.0);
	
	omp_set_num_threads (threads);

    #pragma omp parallel for private (i,j,k)

	for (i = 1; i < L-1; i++) {
		for (j = 1; j < C-1; j++){       
			for (k = 1; k < P-1; k++){        
		    	cubonew[i][j][k] = divBy * ( 
		    			cubo[i-1][j][k] + 
		    			cubo[i][j-1][k] + 
		    			cubo[i][j][k-1] + 
		    			cubo[i+1][j][k] + 
		    			cubo[i][j+1][k] + 
		    			cubo[i][j][k+1] );
			}
		}
	}

	#pragma omp parallel for private (i,j,k)

	for (i = 1; i < L-1; i++) {
		for (j = 1; j < C-1; j++){			        
			for (k = 1; k < P-1; k++){			        
		    	cubo[i][j][k] = cubonew[i][j][k];
			}
		}
	}
}
