#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <time.h>
#include <sys/time.h>
#include <malloc.h>
#include "tempo.h"

#define MAX 20000
int vetor[MAX][MAX];
int main(){

	int comm_size;   //Numero de processos total
	int my_rank;   // identificacao do processo
	struct mallinfo mi;
	int num_elem=0;
	int i,j,resto;
	int qtd_por_processo;
	int flag=0,flag_g=0;
	int limite=0;
	double wall0,wall1;
    	double cpu_total=0;
	double cpu0,cpu1,cpu_local;
	
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	do{
		double start, finish;
		flag_g = 0;
		flag = 0;
		if(my_rank==0){
			wall0 = get_wall_time();
			//printf("\nEntre com o número de elementos: ");
			scanf("%d",&num_elem);
			if(num_elem == 0){
				return 0;
		}
		}
		
		MPI_Bcast(&num_elem, 1, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Barrier(MPI_COMM_WORLD);
		if(my_rank==0){
		//printf("\nEntre com o vetor:\n");
		for(i = 0; i < num_elem; i++){
                        for(j = 0; j < num_elem; j++){
                                scanf(" %d", &vetor[i][j]);
                        }
                }
                }
                MPI_Barrier(MPI_COMM_WORLD);
               
                
		MPI_Bcast(vetor, MAX*MAX, MPI_INT, 0, MPI_COMM_WORLD);
		
		
		
		MPI_Barrier(MPI_COMM_WORLD);
		
		qtd_por_processo = (num_elem/comm_size);
		resto = (num_elem%comm_size);
		if(my_rank==0){
			if(resto==0){
			for(i=1;i<comm_size;i++){	
				limite+=qtd_por_processo;
				MPI_Send(&limite,1,MPI_INT,i,0,MPI_COMM_WORLD);
			}
		}else{
//Se tiver resto, envia um elemento a mais para os "resto" primeiros processos
			qtd_por_processo++;
			for(i=1;i<resto;i++){
				limite+=qtd_por_processo;
				MPI_Send(&limite,1,MPI_INT,i,0,MPI_COMM_WORLD);
			}
			limite++;
			qtd_por_processo--;
			for(i=resto;i<comm_size;i++){	
				limite+=qtd_por_processo;
				MPI_Send(&limite,1,MPI_INT,i,0,MPI_COMM_WORLD);	
			}
			qtd_por_processo++;
		}
		limite=0;
		}else{
			MPI_Recv(&limite,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		}
		
		if(my_rank < resto){
			qtd_por_processo++;
		}
		GET_TIME(start);
		//printf("\nmy_rank: %d, limite: %d",my_rank,limite);
		for(i=limite;i<limite+qtd_por_processo;i++){
			for(j=0;j<num_elem;j++){
				if(i!=j){
					if(vetor[i][j]==0){
					
					flag=1;
					}
				}else{
					if(vetor[i][j]==1){
					
					flag=1;
					}
				}
			}
		}
		GET_TIME(finish);
		cpu_local=finish-start;
		MPI_Reduce(&flag,&flag_g,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
		MPI_Reduce(&cpu_local,&cpu_total,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
		if(my_rank==0){
			if(flag_g>=1){
				printf("Not Complete!\n");
			}else{
				printf("Complete!\n");
			}
			
		
		wall1 = get_wall_time();
		mi = mallinfo();
		printf("%f\n ",wall1-wall0);
		printf("%f\n ",cpu_total);
		printf("%d\n", mi.uordblks);
		//printf("\nFlag: %d, Flag_g: %d",flag,flag_g);
		//MPI_Bcast(&flag, 1, MPI_INT, 0, MPI_COMM_WORLD);
}
	}while(num_elem!=0);
	MPI_Finalize();
	
      
	return 0;
}
