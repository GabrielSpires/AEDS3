#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Tipo dos elementos na fila.
typedef int TipoFila;

// Define como os elementos da fila serão organizados na memória.
typedef struct nodeFila{
  TipoFila key;
  struct nodeFila* prev;
  struct nodeFila* next;
}NodeFila;

// Define um tipo de dado Fila (Fila).
typedef struct {
  NodeFila* end;  // Ponteiro para o sentinela.
  int size;  // Número de elementos na fila.
}Fila;

// Cria uma fila vazia em O(1).
void criaFila(Fila*);

// Testa se a fila está vazia em O(1).
int filaVazia(Fila*);

// Retorna o número de elementos na fila em O(1).
int tamFila(Fila*);

// Retorna o elemento que está no início da fila em O(1).
// Precondição: a fila não pode estar vazia.
TipoFila frenteFila(Fila*);

// Retorna o elemento que está no final da fila em O(1).
// Precondição: a fila não pode estar vazia.
TipoFila fundoFila(Fila*);

// Insere k no final da fila em O(1).
void enfileirar(TipoFila, Fila*);

// Remove o elemento que está no início da fila em O(1).
// Precondição: a fila não pode estar vazia.
void desenfileirar(Fila*);

// Faz a fila p ficar igual a q em O(n + m),
// onde n = tamFila(p) e m = tamFila(q).
void copy(Fila*, Fila*);

// Libera a memória alocada para todos os elementos da fila em O(n),
// onde n é o número de elementos na fila.
void liberaFila(Fila*);