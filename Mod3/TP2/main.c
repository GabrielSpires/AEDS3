#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ag.h"
#include "fb.h"
#include "pd.h"

int main(int argc, char const *argv[]){
	int t, //num de instancias
		n, //planetas consecutivos de uma rota
		k, //num de planetas a serem reconquistados
		i, j;
	int **distMatriz;
	int *distVetor;
	int printar = 0;
	scanf("%d", &t);

	while(t--){
		scanf("%d %d", &n, &k);
		n += 2;

		distVetor = (int*) malloc(n * sizeof(int));

		distMatriz = (int**) calloc(n , sizeof(int*));
		for(i=0; i<n; i++){
			distMatriz[i] = (int*) calloc(n , sizeof(int));
		}

		distMatriz[0][0] = 0;
		distVetor[0] = 0;
		for(i=1; i<n; i++){
			for(j=0; j<n; j++){
				distMatriz[i][j] = 0;
			}

			scanf("%d", &distMatriz[i-1][i]);
			distVetor[i] = distMatriz[i-1][i];
		}
		for(i=2; i<n; i++){
			for(j=0; j<i-1; j++){
				distMatriz[j][i] += distMatriz[i-1][i] + distMatriz[j][i-1];
			}
		}

		if(printar){
			for(i=0; i<n; i++){
				printf("%d ", distVetor[i]);
			}printf("\n");

			printf("  ");
			for(i=0; i<n; i++) printf(" %2d ", i);
			printf("\n  +");
			for(i=0; i<n; i++) printf("---+");
			printf("\n");
			for(i=0; i<n; i++){ 
				printf("%d |", i);
				for(j=0; j<n; j++){
					if(distMatriz[i][j] != 0) printf("%2d |", distMatriz[i][j]);
					else printf("   |");
				}printf("\n  +");
				for(j=0; j<n; j++) printf("---+");
				printf("\n");
			}
		}
		
		if(!strcmp(argv[1], "-a") && !strcmp(argv[2], "PD")){
			printf("Executar PD\n");
		}else if(!strcmp(argv[1], "-a") && !strcmp(argv[2], "AG")){
			// printf("Executar AG\n");
			ag(n, k, distVetor);
		}else if(!strcmp(argv[1], "-a") && !strcmp(argv[2], "FB")){
			// printf("Executar FB\n");
			fb(n, k, distVetor);
		}else{
			printf("ERRO! ARGUMENTO INVALIDO!\n");
		}
		for(i=0; i<n; i++) free(distMatriz[i]);
		free(distMatriz);
	}

	return 0;
}