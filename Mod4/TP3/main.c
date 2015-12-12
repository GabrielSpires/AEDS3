#include "funcoes.h"

typedef struct{
	int valores[400], //Vetor que armazena cada conjunto de números
		qtdV,		  //Variável que indica quantos elementos foram lidos
		tamConj;	  //Tamanho do subconjunto na combinação
}Arg;

void fooR(int* src, int* v, int srcIndex, int vIndex, int srcSize, int vSize){
	int i;
	if(vIndex==vSize){
		for(i=0; i<vSize; i++)
			printf("%d ", v[i]);
		printf("\n");
	}
	else{
		for(i=srcIndex; i<srcSize; i++){
			v[vIndex] = src[i];
			fooR(src, v, i+1, vIndex+1, srcSize, vSize);
		}
	}
}

void foo(int* src, int size, int k){
	int *v;
	v = (int*)calloc(k, sizeof(int));
	fooR(src, v, 0, 0, size, k);
}

int main(int argc, char const *argv[]){
	if(strcmp(argv[1], "-t") == 0){
		int i, j,
			achou, 
			numThreads = atoi(argv[2]);
		int t, 			  //número de instâncias do problema a serem simuladas
			soma, 		  //valor da soma
			total; 		  //Variável que guarda a soma de todos os elementos
		Arg in;	  		  //Struct que guarda os valores da entrada
		char proxChar; 	  //char que recebe o caractere após cada número

		pthread_t threads[numThreads];

		scanf("%d", &t);

		while(in.qtdV = 0, total = 0, achou=0, t--){
			scanf("%d", &soma);

			do{
				scanf("%d%c", &in.valores[in.qtdV], &proxChar);
				/*Poda*/
					if(in.valores[in.qtdV] == soma){
						printf("sim\n");
						achou = 1;
						proxChar = '\n';
						continue;
					}
				/**/
				total+= in.valores[in.qtdV]; //soma todos os valores da entrada
				in.qtdV++;
			}while(proxChar != '\n'); //quando o próximo char é '\n' para de ler
			
			// Se a soma é um dos valores da entrada então ela já foi encontrada
			if(achou) continue;

			/*se a soma total é menor que a soma procurada,
			então não precisamos buscar nos subgrupos já que
			a soma nunca será encontrada*/
			if(total < soma){
				printf("nao\n");
				continue;
			}
			if(soma == 0){
				printf("sim\n");
				continue;
			}

			for(i=1; in.tamConj=i, i<soma; i++){
				// for(j=0; j<numThreads; j++){
				// 	pthread_create(&threads[j], NULL, foo, (void*)&in);
				// }
				foo(&in.valores[0], in.qtdV, i);
			}

			// if(achaSomaPD(in.valores, in.qtdV, soma)) //O(( qtdV+1)*(soma+1) )
			// 	printf("sim\n");
			// else
			// 	printf("nao\n");
		}
	}
	return 0;
}