#include <stdio.h>
#include <string.h>
#include <pthread.h>
// #include <semaphore.h>
#include <stdlib.h>

// int cmpInt(const void* a, const void* b){
//   return *(int*)a - *(int*)b;
// }

int achaSoma(int valores[], int qtdV, int soma){
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

int main(int argc, char const *argv[]){
	if(strcmp(argv[1], "-t") == 0){
		int t, //número de instâncias do problema a serem simuladas
			soma, //valor da soma
			total, //Variável que guarda a soma de todos os elementos
			valores[300], //vetor que armazena cada conjunto de números
			qtdV; //variável que indica quantos elementos foram armazenados
		char proxChar; //char que recebe o caractere após cada número

		scanf("%d", &t);

		while(qtdV = 0, total = 0, t--){
			scanf("%d", &soma);

			do{
				scanf("%d%c", &valores[qtdV], &proxChar);
				total+= valores[qtdV];//soma todos os valores da entrada
				qtdV++;
			}while(proxChar != '\n'); //quando o próximo char é '\n' para de ler

			/*se a soma total é menor que a soma procurada,
			então não precisamos buscar nos subgrupos já que
			a soma nunca será encontrada*/
			if(total < soma){
				printf("nao\n");
				continue;
			}

			if(achaSoma(valores, qtdV, soma)) //O(( qtdV+1)*(soma+1) )
				printf("sim\n");
			else
				printf("nao\n");
		}
	}
	return 0;
}