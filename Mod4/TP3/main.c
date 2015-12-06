#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

#define true 1
#define false 0
typedef int bool;

// int cmpInt(const void* a, const void* b){
//   return *(int*)a - *(int*)b;
// }

bool isSubsetSum(int set[], int n, int sum)
{
    // The value of subset[i][j] will be true if there is a subset of set[0..j-1]
    //  with sum equal to i
    bool subset[sum+1][n+1];
 
    // If sum is 0, then answer is true
    for (int i = 0; i <= n; i++)
      subset[0][i] = true;
 
    // If sum is not 0 and set is empty, then answer is false
    for (int i = 1; i <= sum; i++)
      subset[i][0] = false;
 
     // Fill the subset table in botton up manner
     for (int i = 1; i <= sum; i++)
     {
       for (int j = 1; j <= n; j++)
       {
         subset[i][j] = subset[i][j-1];
         if (i >= set[j-1])
           subset[i][j] = subset[i][j] || subset[i - set[j-1]][j-1];
       }
     }
 
    /*
    // uncomment this code to print table
     for (int i = 0; i <= sum; i++)
     {
       for (int j = 0; j <= n; j++)
          printf ("%4d", subset[i][j]);
       printf("\n");
     }
     */
 
     return subset[sum][n];
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

			if(isSubsetSum(valores, qtdV, soma))
				printf("sim\n");
			else
				printf("nao\n");
		}
	}
	return 0;
}