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
    	double start,finish,cpu_total;
        int thread_count = strtol(argv[1], NULL, 10);
	struct mallinfo mi;
	wall0 = get_wall_time();
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
                
    		
                flag = 1;
		
		#pragma omp parallel private(start,finish) num_threads(thread_count)
		{
		GET_TIME(start);
                #pragma omp parallel for private(i,j) shared(cpu_total) num_threads(thread_count)
                for(i = 0; i < tam; i++){
                        for(j = 0; j < tam; j++){
                                if((!num[i][j] && (i!=j))){ //diagonal sem ciclo
                                        flag = 0;
                                        break;
                                }
                        }
                }
		GET_TIME(finish);
		#pragma omp critical
		cpu_total+=(finish-start);
		}
                wall1 = get_wall_time();
    		
		mi = mallinfo();
                if(flag) printf("É completo\n");
                else printf("Não é completo\n");

		printf("%f\n ",wall1-wall0);
		printf("%f\n ",cpu_total);
		printf("%d\n",mi.uordblks);
                for(i = 0; i < tam; i++)free(num[i]);
                free(num);
        
        }while(tam != 0);
        return 0;
}
