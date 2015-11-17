#include "fb.h"

void calcularDist(short int *visitar, int numPlanetas, int *distVetor, int *solucao){
	/*Vetor cópia do vetor de distancias original criado para que
	o original permaneça o mesmo entre uma chamada e outra da função*/
	int distAuxiliar[numPlanetas];

	/*Variável que guarda a maior sub-distancia
	dessa solução*/
	int maiorSubDist = 0, j, i;
	
	/*Copia o vetor de distancias no auxiliar*/
	for(i=0; i<=numPlanetas; i++){
		distAuxiliar[i] = distVetor[i];
	}

	/*Loop que roda o vetor todo buscando as posições a serem somadas*/
	for(i=1; i<numPlanetas; i++){
		/*Se uma posição nao deve ser visitada ela é somada com a próxima*/
		if(!visitar[i]){
			j = i;
			/*Enquanto a proxima posição no vetor não deve ser visitada ou o 
			loop não chegar no final do vetor, sua distância é somada com a
			primeira posição a ser pulada*/
			for(; j<numPlanetas && !visitar[j]; j++){
				distAuxiliar[i] += distAuxiliar[j+1];
			}
		}
	}
	
	/*Busca no vetor qual é a maior sub-distância*/
	for(i=0; i<=numPlanetas; i++){
		if(maiorSubDist < distAuxiliar[i]){
			maiorSubDist = distAuxiliar[i];
		}
	}

	/*Testa se a solução atual é pior que a encontrada nessa combinação,
	se for o valor da solução é atualizado*/
	if(*solucao > maiorSubDist){
		*solucao = maiorSubDist;
	}

}

void gerarCombinacoes(int *distVetor, int* indices, int* combinacao, int indPlaneta, int indVetor, int numPlanetas, int aConquistar, int *solucao){
	/*Vetor binário que controla se o planeta na posição x do vetor deve ser
	visitado ou não*/
	short int *visitar;
	visitar = (short int*)calloc(numPlanetas, sizeof(short int));
	int i;

	if(indVetor == aConquistar){
		for(i=0; i<aConquistar; i++){
			//Seta as posições que devem ser visitadas
			visitar[combinacao[i]] = 1;
		}
		//Com o vetor setado, as distâncias são calculadas
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
	int solucao = INT_MAX, //Variável que guarda o valor da menor maior subDist
		i;
	int *combinacao; //Vetor de posições que é alterado na combinação
	combinacao = (int*)calloc(aConquistar, sizeof(int));
	
	//Vetor que possui apenas os números dos índices para ser usado na combinação
	int *indices = (int*)malloc(numPlanetas*sizeof(int));
	for(i=0; i<numPlanetas; i++) indices[i] = i;

	//Roda a força bruta gerando as combinações de escolhar de planetas
	gerarCombinacoes(distVetor, indices, combinacao, 1, 0, numPlanetas-1, aConquistar, &solucao);

	printf("%d\n", solucao);
}