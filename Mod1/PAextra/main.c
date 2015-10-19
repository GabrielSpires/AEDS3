#include "lista.h"

int global = 0;

int percorre(int n, int v, lista* vetorAdj, short int* visitado){
    int i=0, k=0;
    iterador j;
    visitado[v] = 1;

    // for(i=1; i<=n; i++){
    // 	printf("%d ", visitado[i]);
    // }printf("\n");//Printa o vetor de visita
    if(vetorAdj[v].tamanho != 0){
		for (j = inicio(&vetorAdj[v]); j != final(&vetorAdj[v]); j = next(j)){
			if(visitado[j->key] == 1){
				global = 1;
			}
			else if(visitado[j->key] == 0){
				percorre(n, j->key, vetorAdj, visitado);
			}
		}
	}
	visitado[v] = 2;

    return 0;
}

int main(int argc, char const *argv[])
{
	/*
	* n = vertices
	* m = arestas
	* a e b = origem e destino da aresta
	*/
	int t, n, m;
	Chave a, b;
	lista* vetorAdj;
	iterador i;
	int j;
	short int* visitado;

	scanf("%d", &t); //Casos de teste
	while(t--){
		scanf("%d %d", &n, &m); //N° de vertices e arestas
		visitado = (short int*)calloc((n+1), sizeof(short int));
		vetorAdj = (lista*)malloc((n+1)*sizeof(lista)); //Aloca um vetor de n listas
		
		for(j=1; j<=n; j++){
			criaLista(&vetorAdj[j]);
		}
		while(m--){
			scanf("%d %d", &a, &b); //Aresta
			inserir(b, &vetorAdj[a]); //Insere o vertice b na lista do vertice a
		}
		for(j=1; j<=n; j++){
			percorre(n, j, vetorAdj, visitado);
		}
		if(global) printf("SIM\n");
		else printf("NAO\n");

		for(j=1; j<=n; j++){
	    	visitado[j] = 0; //Reseta o vetor de visita
	    }

	    global = 0;
		for (j=1; j < n; j++){
			liberaLista(&vetorAdj[j]);
		}
		free(visitado);
		free(vetorAdj);
	}

	return 0;
}