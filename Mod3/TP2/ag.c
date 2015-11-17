#include "ag.h"

void ag(int numPlanetas, int aConquistar, int *distVetor){
	int i, j, //Variaveis de controle (loops)
		k, //Indice do vetor a ser unido para formar nova sub-distancia
		menorSubDist, //Guarda o valor da soma de duas posiçoes no vetor
		maiorSubDist = 0, //Variavel usada para exibir a maior sub-distancia
		aPular; //Quantidade de planetas a serem ignorados (n-k)
	
	for(aPular = (numPlanetas-2)-aConquistar; aPular > 0; aPular--){
		//Seta como menor sub-distancia a distancia entre o inicio e o planeta 2
		menorSubDist = distVetor[1]+distVetor[2];

		//Inicialmente as distancias a serem somadas sao as posiçoes k e k+1
		//A variavel k representa o indice no vetor distVetor
		k = j = 1;

		//Procura no vetor uma soma consecutiva que seja menor que a anterior
		while(j < numPlanetas-1){
			//Testa se a proxima soma é menor que a setada anteriormente 
			if(menorSubDist > distVetor[j]+distVetor[j+1]){

				//Se uma menor sub-distancia for encontrada, ela eh atualizada
				menorSubDist = distVetor[j]+distVetor[j+1];

				//Atualiza tambem o indice a ser usado como referencia
				k = j;
			}			
			j++;
		}
		// printf("Somou %d com %d\n", distVetor[k], distVetor[k+1]);
		//Coloca a soma (menor sub-distancia encontrada) na posiçao k do vetor
		distVetor[k] = menorSubDist;

		//Desloca o vetor uma posiçao para a esquerda a partir do indice k
		for(i=k+1; i<numPlanetas; i++){
			distVetor[i] = distVetor[i+1];
		}

		//Numero de planetas é diminuido, uma vez que o vetor encolheu de 1
		numPlanetas--;
	}

	//Acha qual eh a maior sub-distancia encontrada a exibe
	for(i=1; i<numPlanetas; i++){
		if(maiorSubDist < distVetor[i]){
			maiorSubDist = distVetor[i];
		}
	}
	printf("%d\n", maiorSubDist);
}