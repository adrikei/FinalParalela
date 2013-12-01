/*
 * Grupo 13:
 * 329550-Adriano Pais Rodrigues
 * 380075-Arthur Pessoa de Souza
 * 379980-João Eduardo Brandes Luiz
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
	int tam, i, j, flag;
	int** num;
	
	do{
		scanf("%d", &tam);
		if(!tam) return 0;

		num = (int**) malloc(sizeof(int*)*tam);
		
		for(i = 0; i < tam; i++)num[i] = (int*) malloc(sizeof(int)*tam);
		
		for(i = 0; i < tam; i++){
			for(j = 0; j < tam; j++){
				scanf("%d", &num[i][j]);
			}
		}
		
		flag = 1;
		#pragma omp parallel for private(i,j, num)
		for(i = 0; i < tam; i++){
			for(j = 0; j < tam; j++){
				if((!num[i][j] && (i!=j))){ //diagonal sem ciclo
					flag = 0;
					break;
				}
			}
		}
		
		if(flag) printf("É completo\n");
		else     printf("Não é completo\n");

		for(i = 0; i < tam; i++)free(num[i]);
		free(num);
	
	}while(tam != 0);
	return 0;
}
