#include "lista.h"
#include "fila.h"

typedef struct{
	int quarteirao; //Numero do quarteirao (0, 1, 2, ..., q)
	double probFogo;//Numero de [0,1] que representa a probabilidade de incendio
}itemHeap;

typedef struct{
	itemHeap *vetor; //Vetor com cada quarteirao inserido no Heap
	int *posHeap; //Vetor que guarda as posiçoes de cada elemento no Heap
	int sizeHeap; //Tamanho do Heap = numero de elementos inseridos
}Heap;

typedef itemHeap TipoItem;
typedef double TipoChave;

Heap vetorQ;

void trocaItemHeap(itemHeap *a, itemHeap *b, int *posHeap);

void refazBaixoCima(Heap*, int /*, int* */);

void refazCimaBaixo(Heap* /*, int* */);

int retiraHeap(Heap* /*, int* */);

void insereHeap(Heap*, double, int /*, int* */);

void liberaHeap(Heap*);

void constroiHeap(Heap *, int);