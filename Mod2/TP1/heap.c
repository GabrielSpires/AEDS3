#include "heap.h"

void troca(itemHeap *a, itemHeap *b){
	itemHeap temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void refazBaixoCima(Heap *a, int *posHeap){
	int k = a->sizeHeap;
	// se pai for menor que filho, troca
	while(k > 1 && a->vetor[k/2].probFogo < a->vetor[k].probFogo){
		troca(&a->vetor[k], &a->vetor[k/2]);
		int temp = posHeap[a->vetor[k].quarteirao];
		posHeap[a->vetor[k].quarteirao] = posHeap[a->vetor[k/2].quarteirao];
		posHeap[a->vetor[k/2].quarteirao] = temp;
		// vai pro pai e repete o processo
		k = k/2;
	}
}

void refazCimaBaixo(Heap *a, int *posHeap){
	int j;
	int dir = a->sizeHeap;
	int k = 1;
	while(2*k <= dir){
		j = 2*k;
		// encontra o maior filho
		if(j+1 < dir && a->vetor[j].probFogo < a->vetor[j+1].probFogo)
			j++;
		// testa se pai eh maior que filho
		if(a->vetor[k].probFogo >= a->vetor[j].probFogo)
			break;
		// pai eh menor que filho, troca posiçoes
		troca(&a->vetor[k], &a->vetor[j]);
		int temp = posHeap[a->vetor[k].quarteirao];
		posHeap[a->vetor[k].quarteirao] = posHeap[a->vetor[j].quarteirao];
		posHeap[a->vetor[j].quarteirao] = temp;
		k = j;
	}
}

void retiraHeap(Heap *a, int *posHeap){
	//cimaBaixo
	a->vetor[1] = a->vetor[a->sizeHeap];
	a->sizeHeap--;
	if(a->sizeHeap > 0)
		refazCimaBaixo(a, posHeap);
}

void insereHeap(Heap *a, double probF, int quart, int *posHeap){
	//baixoCima
	a->sizeHeap++;
	a->vetor[a->sizeHeap].quarteirao = quart;
	a->vetor[a->sizeHeap].probFogo = probF;
	posHeap[quart] = a->sizeHeap;
	refazBaixoCima(a, posHeap);
}

void constroiHeap(Heap *a, int tamMax){
	a->vetor = (TipoItem*)malloc(1 + (tamMax * sizeof(TipoItem)));
	a->sizeHeap = 0;
}