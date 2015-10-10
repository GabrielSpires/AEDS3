#include "lista.h"

int main(){
	int* grupos;
	char minhaPalavra[51];
	char separador;
	int n;
	lista palavras;

	scanf("%d", &n);
	while(n--){ //O(n)
		criaLista(&palavras);
		do{ //O(p)
			scanf("%s%c", minhaPalavra, &separador); //O(1)
			qsort(minhaPalavra, strlen(minhaPalavra), sizeof(char), cmp); //O(c*logc)
			inserir(minhaPalavra, &palavras); //O(a)
		}while(separador == ' ');

		grupos = (int*)calloc(tamanho(&palavras), sizeof(int)); //O(1)

		iterador i;
		int j = 0;
		for (i = inicio(&palavras); i != final(&palavras); i = next(i)){ //O(p)
			grupos[j] = i->tam;
			j++;
		}

		qsort(grupos, tamanho(&palavras), sizeof(int), cmpInt); //O(p*logp)

		for (j = tamanho(&palavras)-1; j >= 0 ; j--){ //O(p)
			printf("%d ", grupos[j]);
		}
		printf("\n");

		free(grupos); //O(1)
		liberaLista(&palavras); //O(p)
	}

	return 0;
}