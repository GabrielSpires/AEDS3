#include "heap.h"

void troca(TipoChave *a, TipoChave *b){
	TipoChave temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void refazBaixoCima(TipoChave *a, int k){
	// se pai for menor que filho, troca
	while(k > 1 && a[k/2] < a[k]){
		troca(&a[k], &a[k/2]);
		// vai pro pai e repete o processo
		k = k/2;
	}
}

void refazCimaBaixo(TipoChave *a, int k, int dir){
	int j = 0;
	while(2*k <= dir){
		j = 2*k;
		// encontra o maior filho
		if(j < dir && a[j] < a[j+1])
			j++;
		// testa se pai eh maior que filho
		if(a[k] >= a[j])
			break;
		// pai eh menor que filho, troca posiçoes
		troca(&a[k], &a[j]);
		k = j;
	}
}

void constroiHeap(TipoChave *a, int n){
	int esq = 0;

	esq = (n/2) + 1;
	while(esq > 1){
		esq--;
		refazCimaBaixo(a, esq, n);
	}
}

void heapsort(TipoChave *a, int n){
	int esq, dir;

	constroiHeap(a, n);
	esq = 0;
	dir = n-1;
	// ordena o vetor
	while(dir > 0){
		troca(&a[0], &a[dir]);
		dir--;
		refazCimaBaixo(a, esq, dir);
	}
}