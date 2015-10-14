#include "lista.h"
#include "fila.h"

typedef struct{
	int quarteirao;
	double probFogo;
}itemHeap;

typedef struct{
	itemHeap *vetor;
	int sizeHeap;
}Heap;

typedef itemHeap TipoItem;
typedef double TipoChave;

Heap vetorQ;

void troca(TipoItem*, TipoItem*);

void refazBaixoCima(Heap*, int*);

void refazCimaBaixo(Heap*, int*);

int retiraHeap(Heap*, int*);

void insereHeap(Heap*, double, int, int*);

void constroiHeap(Heap *, int);