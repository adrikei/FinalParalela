#include <stdio.h>

int main(int argc, char *argv[]) {
	int tam, i, j, num, flag;
	scanf("%d", &tam);
	while(tam != 0){
		flag = 1;
		for(i = 0; i < tam; i++){
			for(j = 0; j < tam; j++){
				scanf("%d", &num);
				if(!num)
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
	return 0;
}
