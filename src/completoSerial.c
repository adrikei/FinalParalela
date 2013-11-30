#include <stdio.h>
#include <stdlib.h>

#define MAX 10000

int main(int argc, char *argv[]) {
	int tam, i, j, flag;
	int** num;
	
	scanf("%d", &tam);
	num = (int**) malloc(sizeof(int*)*MAX);
	
	for(i = 0; i < MAX; i++){
		num[i] = (int*) malloc(sizeof(int)*MAX);
	}
	
	while(tam != 0){
		
		for(i = 0; i < tam; i++){
			for(j = 0; j < tam; j++){
				scanf("%d", &num[i][j]);
			}
		}
		
		flag = 1;
		for(i = 0; i < tam; i++){
			for(j = 0; j < tam; j++){
				if(!num[i][j])
					flag = 0;
			}
		}
		
		if(flag){
			printf("É completo\n");
		}else{
			printf("Não é completo\n");
		}
		scanf("%d", &tam);	
	}
	
	for(i = 0; i < MAX; i++){
		free(num[i]);
	}
	
	free(num);
		
	return 0;
}
