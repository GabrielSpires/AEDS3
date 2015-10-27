#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[]){
	int t, //num de instancias
		n, //planetas consecutivos de uma rota
		k, //num de planetas a serem reconquistados
		i;
	int *dist = NULL;
	int printar = 1;
	scanf("%d", &t);

	while(t--){
		printf("%d\n", t);
		scanf("%d %d", &n, &k);
		n++;
		dist = (int*)malloc(n * sizeof(int));

		if(printar) printf("\n    ");
		for(i=0; i<n; i++){
			scanf("%d", &dist[n]);
			if(printar) printf("%d       ", dist[n]);
		}
		if(printar) printf("\nI------>");
		if(printar) for(i=0; i<n-1; i++){
			if(i < n-1) printf("P%d----->", i+1);
			else printf("P%d", i+1);
		}if(printar) printf("F\n\n");

		if(!strcmp(argv[1], "-PD")){
			printf("Executar PD\n");
		}else if(!strcmp(argv[1], "-AG")){
			printf("Executar AG\n");
		}else if(!strcmp(argv[1], "-FB")){
			printf("Executar FB\n");
		}else{
			printf("ERRO! ARGUMENTO INVALIDO!\n");
		}
		free(dist);
	}

	return 0;
}