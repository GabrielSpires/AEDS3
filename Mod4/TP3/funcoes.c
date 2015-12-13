#include "funcoes.h"

int cmpInt(const void* a, const void* b){
  return *(int*)a - *(int*)b;
}

void bar(long* cal, long* subGrp, int calIndx, int subIndx, int calTam, int subTam, long soma){
	if(somaAchada) return;
	// printf("AEHOOOO:::%d\n", subTam);
	
	int i, somaSubGrupo = 0;
	
	if(subIndx==subTam){
		for(i=0; i<subTam; i++){
			somaSubGrupo += subGrp[i];
			printf("%ld ", subGrp[i]);
		}
		if(somaSubGrupo == soma){
			somaAchada = 1;
		}
		printf("\n");
	}
	else{
		for(i=calIndx; i<calTam; i++){
			subGrp[subIndx] = cal[i];
			bar(cal, subGrp, i+1, subIndx+1, calTam, subTam, soma);
		}
	}
}

void *foo(void *argumento){
	Arg *in = (Arg*)argumento;

	
	printf("in.tamConj:::%ld\n", in->tamConj);

	long *subGrp;
	subGrp = (long*)calloc(in->tamConj, sizeof(long));

	bar(in->valores, subGrp, 0, 0, in->qtdV, in->tamConj, in->soma);

	free(subGrp);
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