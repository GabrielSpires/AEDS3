#include "fb.h"

void gerarCombinacoes(int* distVetor, int* v, int indPlaneta, int vIndex, int numPlanetas, int aConquistar){
	int i;
	if(vIndex == aConquistar){
		for(i=0; i<aConquistar; i++)
			printf("%d ", v[i]);
		printf("\n");
	}
	else{
		for(i=indPlaneta; i<numPlanetas; i++){
			v[vIndex] = distVetor[i];
			gerarCombinacoes(distVetor, v, i+1, vIndex+1, numPlanetas, aConquistar);
		}
	}
}

void fb(int numPlanetas, int aConquistar, int *distVetor){
	int *v;
	v = (int*)calloc(aConquistar, sizeof(int));
	gerarCombinacoes(distVetor, v, 1, 0, numPlanetas-1, aConquistar);

	// foo(distVetor, numPlanetas, aConquistar);
	//olhar se maior distancia do grafo
	//é menor que a maior dos outros
}