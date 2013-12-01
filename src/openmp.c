/*
* Grupo 13:
* 329550-Adriano Pais Rodrigues
* 380075-Arthur Pessoa de Souza
* 379980-João Eduardo Brandes Luiz
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <sys/time.h>
#include <malloc.h>
#include "tempo.h"

int main(int argc, char *argv[]) {
        int tam, i, j, flag;
        int** num;
        double wall0,wall1;
    	double cpu0,cpu1;
        int thread_count = strtol(argv[1], NULL, 10);
	struct mallinfo mi;
        do{
                scanf("%d", &tam);
                if(!tam) return 0;

                num = (int**) malloc(sizeof(int*)*tam);
                
                for(i = 0; i < tam; i++){
		num[i] = (int*) malloc(sizeof(int)*tam);
		}	
                
                for(i = 0; i < tam; i++){
                        for(j = 0; j < tam; j++){
                                scanf("%d", &num[i][j]);
                        }
                }
                wall0 = get_wall_time();
    		cpu0  = get_cpu_time();
                flag = 1;
                #pragma omp parallel for private(i,j) num_threads(thread_count)
                for(i = 0; i < tam; i++){
                        for(j = 0; j < tam; j++){
                                if((!num[i][j] && (i!=j))){ //diagonal sem ciclo
                                        flag = 0;
                                        break;
                                }
                        }
                }
                wall1 = get_wall_time();
    		cpu1  = get_cpu_time();
		mi = mallinfo();
                if(flag) printf("É completo\n");
                else printf("Não é completo\n");

		printf("%f\n ",wall1-wall0);
		printf("%f\n ",cpu1-cpu0);
		printf("%d\n",mi.uordblks);
                for(i = 0; i < tam; i++)free(num[i]);
                free(num);
        
        }while(tam != 0);
        return 0;
}
