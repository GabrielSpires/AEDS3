#include "heap.h"

void trocaItemHeap(itemHeap *a, itemHeap *b, int *posHeap){
	// printf("QUARTEIRAO %d %d\n", a->quarteirao, b->quarteirao);
	int posTemp = posHeap[b->quarteirao];
	posHeap[b->quarteirao] = posHeap[a->quarteirao];
	posHeap[a->quarteirao] = posTemp;

	itemHeap temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void refazBaixoCima(Heap *meuHeap){
	int k = meuHeap->sizeHeap;
	//Roda ate o inicio do vetor. Se pai < filho troca //k/2 = pai //k = filho
	while(k > 1 && meuHeap->vetor[k/2].probFogo < meuHeap->vetor[k].probFogo){
		if(meuHeap->sizeHeap > 0) trocaItemHeap(&meuHeap->vetor[k], &meuHeap->vetor[k/2], meuHeap->posHeap);
		k /= 2;
	}
}

void refazCimaBaixo(Heap *meuHeap){
	int j = 0,
		k = 1,
		dir = meuHeap->sizeHeap;
	while( (k*2) <= dir ){
		j = k * 2;
		//Descobre qual dos filhos eh maior
		if(j+1 < dir && meuHeap->vetor[j].probFogo < meuHeap->vetor[j+1].probFogo){
		 	j++; //j vira o maior dos filhos
		}
		//Se o pai for >= ao maior dos filhos, pare
		if(meuHeap->vetor[k].probFogo >= meuHeap->vetor[j].probFogo){
			break;
		}
		//Se pai for < que maior dos filhos, troca os dois
		if(meuHeap->sizeHeap > 0) trocaItemHeap(&meuHeap->vetor[k], &meuHeap->vetor[j], meuHeap->posHeap);
		k = j;
	}
}

int retiraHeap(Heap *meuHeap){
	//Variavel recebe o numero do quarteirao removido
	int itemRemovido = meuHeap->vetor[1].quarteirao;

	//Joga o ultimo elemento do heap na raiz
	if(meuHeap->sizeHeap > 0) trocaItemHeap(&meuHeap->vetor[1], &meuHeap->vetor[meuHeap->sizeHeap], meuHeap->posHeap);
	meuHeap->sizeHeap--;
	if(meuHeap->sizeHeap > 0){
		refazCimaBaixo(meuHeap);
	}
	return itemRemovido;
}

void insereHeap(Heap *meuHeap, double probF, int quart){
	meuHeap->sizeHeap++;
	meuHeap->vetor[meuHeap->sizeHeap].quarteirao = quart;
	meuHeap->vetor[meuHeap->sizeHeap].probFogo = probF;
	meuHeap->posHeap[quart] = meuHeap->sizeHeap;
	if(meuHeap->sizeHeap > 1){
		refazBaixoCima(meuHeap);
	}
}

void constroiHeap(Heap *meuHeap, int tamMax){
	meuHeap->vetor = (TipoItem*)malloc(1 + (tamMax * sizeof(TipoItem)));
	meuHeap->posHeap = (int*)calloc(1 + tamMax , sizeof(int));
	meuHeap->sizeHeap = 0;
}