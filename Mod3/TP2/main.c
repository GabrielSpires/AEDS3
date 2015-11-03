#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INF 1.0/0.0

//MODELAR COMO GRAFO
//TENTAR USAR MATRIZ
int main(int argc, char const *argv[]){
	int t, //num de instancias
		n, //planetas consecutivos de uma rota
		k, //num de planetas a serem reconquistados
		i, j, m;
	int **dist;
	// int printar = 0;
	scanf("%d", &t);

	while(t--){
		scanf("%d %d", &n, &k);
		n += 2;
		dist = (int**) calloc(n , sizeof(int*));
		for(i=0; i<n; i++){
			dist[i] = (int*) calloc(n , sizeof(int));
		}

		for(i=1; i<n; i++){
			scanf("%d", &dist[i-1][i]);
		}
		for(i=2; i<n; i++){
			for(j=0; j<i-1; j++){
				dist[j][i] += dist[i-1][i] + dist[j][i-1];
			}
		}
		
		printf("  ");
		for(i=0; i<n; i++) printf(" %2d ", i);
		printf("\n  +");
		for(i=0; i<n; i++) printf("---+");
		printf("\n");
		for(i=0; i<n; i++){ 
			printf("%d |", i);
			for(j=0; j<n; j++){
				if(dist[i][j] != 0) printf("%2d |", dist[i][j]);
				else printf("%2d |", dist[i][j]);
			}printf("\n  +");
			for(m=0; m<n; m++) printf("---+");
			printf("\n");
		}
		
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