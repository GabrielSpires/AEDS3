#include "funcoes.h"

int main(int argc, char const *argv[]){
	if(strcmp(argv[1], "-t") == 0){
		int i, j, k,
			numThreads,	  //Número de threads usadas (argumento do programa)
			t, 			  //Número de instâncias do problema a serem simuladas
			total; 		  //Variável que guarda a soma de todos os elementos
		Arg in;	  		  //Struct que guarda os valores da entrada
		char proxChar; 	  //Char que recebe o caractere após cada número

		numThreads = atoi(argv[2]);
		pthread_t threads[numThreads];

		scanf("%d", &t);

		while(in.qtdV=0, total=0, somaAchada=0, t--){
			scanf("%d", &in.soma);

			do{
				scanf("%d%c", &in.valores[in.qtdV], &proxChar);
				/*Poda de merda*/
					// if(in.valores[in.qtdV] == soma){
					// 	printf("sim\n");
					// 	somaAchada = 1;
					// 	break;
					// }
				/**/
				total+= in.valores[in.qtdV]; //soma todos os valores da entrada
				in.qtdV++;
			}while(proxChar != '\n'); //quando o próximo char é '\n' para de ler
			
			// Se a soma é um dos valores da entrada então ela já foi encontrada
			// if(somaAchada) continue;

			/*se a soma total é menor que a soma procurada,
			então não precisamos buscar nos subgrupos já que
			a soma nunca será encontrada*/
			if(total < in.soma){
				printf("nao\n");
				continue;
			}

			// qsort(&in.valores, in.qtdV, sizeof(int), cmpInt);

			for(i=0; in.tamConj=i, i<in.soma && !somaAchada; i += numThreads){

				for(j=0; j<numThreads; j++){
					pthread_create(&threads[j], NULL, foo, (void*)&in);
					printf(" %d\n", j);

					for(k=0; k<=j; k++){
						pthread_join(threads[k], NULL);
					}

				}
				// foo(&in.valores[0], in.qtdV, i, in.soma);
			}
			if(!somaAchada){
				printf("nao\n");
			}

			// if(achaSomaPD(in.valores, in.qtdV, soma)) //O(( qtdV+1)*(soma+1) )
			// 	printf("sim\n");
			// else
			// 	printf("nao\n");
		}
	}
	return 0;
}