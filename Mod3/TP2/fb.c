#include "fb.h"

void calcularDist(short int *visitar, int numPlanetas, int *distVetor, int *solucao){
	int distAuxiliar[numPlanetas];
	int maiorSubDist = 0, j, i;
	
	for(i=0; i<=numPlanetas; i++){
		distAuxiliar[i] = distVetor[i];
	}

	for(i=1; i<numPlanetas; i++){
		if(!visitar[i]){
			j = i;
			for(; j<numPlanetas && !visitar[j]; j++){
				distAuxiliar[i] += distAuxiliar[j+1];
			}
		}
	}
	
	for(i=0; i<=numPlanetas; i++){
		if(maiorSubDist < distAuxiliar[i]){
			maiorSubDist = distAuxiliar[i];
		}
	}

	if(*solucao > maiorSubDist){
		*solucao = maiorSubDist;
	}

}

void gerarCombinacoes(int *distVetor, int* indices, int* combinacao, int indPlaneta, int indVetor, int numPlanetas, int aConquistar, int *solucao){
	short int *visitar;
	visitar = (short int*)calloc(numPlanetas, sizeof(short int));
	int i;
	if(indVetor == aConquistar){
		for(i=0; i<aConquistar; i++){
			visitar[combinacao[i]] = 1;
		}
		calcularDist(visitar, numPlanetas, distVetor, solucao);
	}
	else{
		for(i=indPlaneta; i<numPlanetas; i++){
			combinacao[indVetor] = indices[i];
			gerarCombinacoes(distVetor, indices, combinacao, i+1, indVetor+1, numPlanetas, aConquistar, solucao);
		}
	}
}

void fb(int numPlanetas, int aConquistar, int *distVetor){
	int solucao = INT_MAX, i;
	int *combinacao;
	combinacao = (int*)calloc(aConquistar, sizeof(int));
	
	int *indices = (int*)malloc(numPlanetas*sizeof(int));
	for(i=0; i<numPlanetas; i++) indices[i] = i;

	gerarCombinacoes(distVetor, indices, combinacao, 1, 0, numPlanetas-1, aConquistar, &solucao);

	printf("%d\n", solucao);
}