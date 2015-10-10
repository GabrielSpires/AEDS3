#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char TipoChave;

void troca(TipoChave*, TipoChave*);

void refazBaixoCima(TipoChave*, int);

void refazCimaBaixo(TipoChave*, int, int);

void constroiHeap(TipoChave*, int);

void heapsort(TipoChave*, int);