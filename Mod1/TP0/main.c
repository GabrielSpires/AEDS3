#include "lista.h"

int main(){
	int* grupos; //vetor que guarda quantos anagramas tem em cada grupo
	char minhaPalavra[51]; //string usada na entrada das palavras
	char separador; //char que testa se a linha acabou
	int n; //numero de casos de teste
	lista palavras; //lista de palavras populada na entrada
	scanf("%d", &n); //recebe quantos casos de teste ser~ao feitos
	while(n--){ //O(n) //Roda n vezes (uma vez para cada teste)
		criaLista(&palavras); //cria uma lista vazia de tamanho 0 e com o sentinela apontando pra si mesmo
		do{ //O(p) //roda enquanto a string estiver antes de um espaço
			scanf("%s%c", minhaPalavra, &separador); //O(1) //recebe a proxima palavra e o caractere seguinte
			qsort(minhaPalavra, strlen(minhaPalavra), sizeof(char), cmp); //O(c*logc) //ordena os caracteres da palavra por ordem alfabetica
			inserir(minhaPalavra, &palavras); //O(a) //insere a palavra ordenada na lista (sem repetiçao)
		}while(separador == ' '); //testa se o caractere adjacente `a palavra eh um espaço

		grupos = (int*)calloc(tamanho(&palavras), sizeof(int)); //O(1) //Aloca o vetor que recebe os grupos com tamanho igual ao de palavras na lista

		iterador i; //variavel do tipo Nodo que eh usada na iteraçao abaixo
		int j = 0; //variavel usada para atualizar a posiçao do vetor grupos
		for (i = inicio(&palavras); i != final(&palavras); i = next(i)){ //O(p) //loop usado para percorrer a lista
			grupos[j] = i->tam; //posiçao do vetor grupos recebe o tamanho do grupo de anagramas do nodo na lista
			j++; //atualiza a variavel de controle
		}

		qsort(grupos, tamanho(&palavras), sizeof(int), cmpInt); //O(p*logp) //ordena o vetor de grupos em ordem crescente

		for (j = tamanho(&palavras)-1; j >= 0 ; j--){ //O(p) //percorre e imprime o vetor de grupos de tras pra frente
			printf("%d ", grupos[j]); //imprime o valor na posiçao j
		}
		printf("\n");

		free(grupos); //O(1) //libera o vetor de grupos
		liberaLista(&palavras); //O(p) //libera a lista
	}

	return 0;
}