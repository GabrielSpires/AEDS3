#include "funcoes.h"

int somaAchada = 0; //Variável global usada pra interromper os testes

typedef struct{
	int valores[400], //Vetor que armazena cada conjunto de números
		qtdV,		  //Variável que indica quantos elementos foram lidos
		tamConj;	  //Tamanho do subconjunto na combinação
}Arg;

void fooR(int* cal, int* subGrp, int calIndx, int subIndx, int calTam, int subTam, int soma){
	int i, somaSubGrupo = 0;
	
	if(somaAchada) return;

	if(subIndx==subTam){
		for(i=0; i<subTam; i++){
			somaSubGrupo += subGrp[i];
			printf("%d ", subGrp[i]);
		}
		if(somaSubGrupo == soma){
			printf("sim\n");
			somaAchada = 1;
			return;
		}printf("\n");
	}
	else{
		for(i=calIndx; i<calTam; i++){
			subGrp[subIndx] = cal[i];
			fooR(cal, subGrp, i+1, subIndx+1, calTam, subTam, soma);
		}
	}
}

void foo(int* cal, int size, int tamSubGrp, int soma){
	int *subGrp;
	subGrp = (int*)calloc(tamSubGrp, sizeof(int));
	fooR(cal, subGrp, 0, 0, size, tamSubGrp, soma);
}

int main(int argc, char const *argv[]){
	if(strcmp(argv[1], "-t") == 0){
		int i, j,
			numThreads,	  //Número de threads usadas (argumento do programa)
			t, 			  //Número de instâncias do problema a serem simuladas
			soma, 		  //Valor da soma
			total; 		  //Variável que guarda a soma de todos os elementos
		Arg in;	  		  //Struct que guarda os valores da entrada
		char proxChar; 	  //Char que recebe o caractere após cada número

		numThreads = atoi(argv[2]);
		// pthread_t threads[numThreads];

		scanf("%d", &t);

		while(in.qtdV = 0, total = 0, somaAchada=0, t--){
			scanf("%d", &soma);

			do{
				scanf("%d%c", &in.valores[in.qtdV], &proxChar);
				/*Poda*/
					if(in.valores[in.qtdV] == soma){
						printf("sim\n");
						somaAchada = 1;
						proxChar = '\n';
						continue;
					}
				/**/
				total+= in.valores[in.qtdV]; //soma todos os valores da entrada
				in.qtdV++;
			}while(proxChar != '\n'); //quando o próximo char é '\n' para de ler
			
			// Se a soma é um dos valores da entrada então ela já foi encontrada
			if(somaAchada) continue;

			/*se a soma total é menor que a soma procurada,
			então não precisamos buscar nos subgrupos já que
			a soma nunca será encontrada*/
			if(total < soma){
				printf("nao\n");
				continue;
			}

			// qsort(&in.valores, in.qtdV, sizeof(int), cmpInt);

			for(i=1; in.tamConj=i, i<soma && !somaAchada; i++){
				// for(j=0; j<numThreads; j++){
				// 	pthread_create(&threads[j], NULL, foo, (void*)&in);
				// }
				foo(&in.valores[0], in.qtdV, i, soma);
			}

			// if(achaSomaPD(in.valores, in.qtdV, soma)) //O(( qtdV+1)*(soma+1) )
			// 	printf("sim\n");
			// else
			// 	printf("nao\n");
		}
	}
	return 0;
}