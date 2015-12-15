#include "funcoes.h"

int cmpInt(const void* a, const void* b){
  return *(int*)a - *(int*)b;
}

void geraCombinacao(int* cal, int* subGrp, int calIndx, int subIndx, int calTam, int subTam, int soma){
	if(somaAchada) return;
	
	int i, somaSubGrupo = 0;
	
	if(subIndx==subTam){
		for(i=0; i<subTam; i++){
			somaSubGrupo += subGrp[i];
			// printf("%d ", subGrp[i]);
		}
		if(somaSubGrupo == soma){
			somaAchada = 1;
			return;
		}
		// printf("\n");
	}
	else{
		if(somaAchada) return;
		for(i=calIndx; i<calTam; i++){
			subGrp[subIndx] = cal[i];
			geraCombinacao(cal, subGrp, i+1, subIndx+1, calTam, subTam, soma);
		}
	}
}

void *calculaIntervalos(void *argumento){
	Arg *in = (Arg*)argumento;

	// printf("in.tamConj:::%d-%d\n", in->tamConjInicial, in->tamConjFinal);

	int *subGrp;
	int i = 0;
	// printf("Inicio: %d Fim:%d\n", in->tamConjInicial, in->tamConjFinal);

	for(i=in->tamConjInicial; i <= in->tamConjFinal; i++){
		if(somaAchada) break;
		subGrp = (int*)calloc(i, sizeof(int));
		// printf("Comb(%d,%d)\n", in->qtdV, i);
		geraCombinacao(in->valores, subGrp, 0, 0, in->qtdV, i, in->soma);

		free(subGrp);
	}
	// pthread_exit(NULL);
}

int achaSomaPD(int valores[], int qtdV, int soma){
	int **subConjunto;
	int i, j;

	subConjunto = (int**)malloc((qtdV+1) * sizeof(int*));
	for(i=0; i<=qtdV; i++) subConjunto[i] = (int*)calloc((soma+1), sizeof(int));

	// Se a soma não for zero e o conjunto for vazio o resultado é 0
	for(i=1; i<=soma; i++){
		subConjunto[0][i] = 0;
	}

	/*Se a soma for 0, então o resultado é 1 uma vez que
	em sub-conjuntos vazios a soma é zero*/
	for(i=0; i<=qtdV; i++){
		subConjunto[i][0] = 1;
	}
 
	// Preenche a matriz de subConjuntos
	for(i=1; i<=qtdV; i++){
		for(j=1; j<=soma; j++){
			subConjunto[i][j] = subConjunto[i-1][j];

			if(j >= valores[i-1]){
				subConjunto[i][j] = subConjunto[i][j] || subConjunto[i-1][j- valores[i-1]];
			}
		}
	}

	// Joga o resultado em uma variável e da free na matriz
	int resultado = subConjunto[qtdV-1][soma];

	for(i=0; i<qtdV; i++) free(subConjunto[i]);
	free(subConjunto);

	return resultado;
}