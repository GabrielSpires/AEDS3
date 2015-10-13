#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int TipoFila;

typedef struct nodeFila{
  TipoFila key;
  int distBomb;
  struct nodeFila* prev;
  struct nodeFila* next;
}NodeFila;

typedef struct {
  NodeFila* end;  // Ponteiro para o sentinela.
  int size;  // Número de elementos na fila.
}Fila;

void criaFila(Fila*);

int filaVazia(Fila*);

int tamFila(Fila*);

TipoFila frenteFila(Fila*);

int distPai(Fila* q);

TipoFila fundoFila(Fila*);

void enfileirar(TipoFila, Fila*, int);

void desenfileirar(Fila*);

// void copy(Fila*, Fila*);

void imprimeFila(Fila*);

void liberaFila(Fila*);