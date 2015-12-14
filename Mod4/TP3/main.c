#include "funcoes.h"

int main(int argc, char const *argv[]){
	// clock_t tempo;
	// tempo = clock();
	if(strcmp(argv[1], "-t") == 0){
		int i, j,
			numThreads,	  //Número de threads usadas (argumento do programa)
			t, 			  //Número de instâncias do problema a serem simuladas
			total; 		  //Variável que guarda a soma de todos os elementos
		Arg in;  		  //Struct que guarda os valores da entrada
		char proxChar; 	  //Char que recebe o caractere após cada número

		numThreads = atoi(argv[2]);
		pthread_t threads[numThreads];

		scanf("%d", &t);

		while(in.qtdV=0, total=0, somaAchada=0, t--){
			scanf("%d", &in.soma);

			do{
				scanf("%d%c", &in.valores[in.qtdV], &proxChar);
				total+= in.valores[in.qtdV]; //soma todos os valores da entrada
				in.qtdV++;
			}while(proxChar != '\n'); //quando o próximo char é '\n' para de ler

			/*se a soma total é menor que a soma procurada,
			então não precisamos buscar nos subgrupos já que
			a soma nunca será encontrada*/
			if(total < in.soma){
				printf("nao\n");
				continue;
			}

			// qsort(&in.valores, in.qtdV, sizeof(int), cmpInt);

			//Cria uma copia da entrada 
			Arg vetIn[numThreads]; //Vetor que guarda os inputs e os intervalos
			int intervalo = in.qtdV/numThreads;

			if(numThreads > in.qtdV) intervalo = 1;

			for(i=0; i<numThreads; i++){
				for(j=0; j<in.qtdV; j++){
					vetIn[i].valores[j] = in.valores[j];
				}
				
				vetIn[i].qtdV = in.qtdV;
				vetIn[i].soma = in.soma;

				//Se tem mais threads que valores algumas threads nao trabalham
				if(i > in.qtdV){
					vetIn[i].tamConjInicial = 0;
					vetIn[i].tamConjFinal = 0;
				}else{
					vetIn[i].tamConjInicial = (i*intervalo)+1;
					if(i < numThreads-1) vetIn[i].tamConjFinal = (i*intervalo)+intervalo;
					else vetIn[i].tamConjFinal = in.qtdV;
				}
				// printf("Thread %d: %d-%d\n", i,vetIn[i].tamConjInicial ,vetIn[i].tamConjFinal);
			}

			// for(i=0; i<numThreads; i++)
			// 	printf("Imain: %d Fmain:%d\n", vetIn[i].tamConjInicial, vetIn[i].tamConjFinal);

			for(i=0; i<numThreads; i++){
				pthread_create(&threads[i], NULL, foo, &vetIn[i]);
			}
			for(i=0; i<numThreads; i++){
				pthread_join(threads[i], NULL);
			}

			if(!somaAchada)
				printf("nao\n");
			else
				printf("sim\n");
		}
	}
	// tempo = clock() - tempo;
	// printf("%f\n", (float)tempo/CLOCKS_PER_SEC);
	
	// pthread_exit(NULL);
	return 0;
}