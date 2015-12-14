#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "ag.h"
#include "fb.h"
#include "pd.h"

int main(int argc, char const *argv[]){
	// clock_t tempo;
	// tempo = clock();
	int t, //num de instancias
		n, //planetas consecutivos de uma rota
		k, //num de planetas a serem reconquistados
		i;
	int *distVetor;
	scanf("%d", &t);

	while(t--){
		scanf("%d %d", &n, &k);
		n += 2;

		distVetor = (int*) malloc(n * sizeof(int));

		distVetor[0] = 0;
		for(i=1; i<n; i++){
			scanf("%d", &distVetor[i]);
		}
		
		if(!strcmp(argv[1], "-a") && !strcmp(argv[2], "PD")){
			// printf("Executar PD\n");
		}else if(!strcmp(argv[1], "-a") && !strcmp(argv[2], "AG")){
			// printf("Executar AG\n");
			ag(n, k, distVetor);
		}else if(!strcmp(argv[1], "-a") && !strcmp(argv[2], "FB")){
			// printf("Executar FB\n");
			fb(n, k, distVetor);
		}else{
			printf("ERRO! ARGUMENTO INVALIDO!\n");
		}
		free(distVetor);
	}
	// tempo = clock() - tempo;
	// printf("%f\n", (float)tempo/CLOCKS_PER_SEC);	

	return 0;
}