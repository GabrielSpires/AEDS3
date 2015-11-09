#ifndef PILHA_H_
#define PILHA_H_

#include <stdio.h>
#include <stdlib.h>

// Tipo dos elementos na pilha.
typedef int TipoPilha;

// Define como os elementos da pilha serão organizados na memória.
typedef struct nodePilha{
  TipoPilha chave;
  int saida;
  struct nodePilha* prev;
  struct nodePilha* next;
} NodePilha;

// Define um tipo de dado Pilha (Pilha).
typedef struct {
  NodePilha* end;  // Ponteiro para o sentinela.
  int tamanho;  // Número de elementos na pilha.
} Pilha;

typedef NodePilha* IteradorPilha;

// Cria uma pilha vazia em O(1).
void criaPilha(Pilha* minhaPilha);

// Testa se a pilha está vazia em O(1).
int pilhaVazia(Pilha* minhaPilha);

// Retorna o número de elementos na pilha em O(1).
int tamPilha(Pilha* minhaPilha);

// Retorna o elemento que está no topo da pilha em O(1).
// Precondição: a pilha não pode estar vazia.
TipoPilha topoPilha(Pilha* minhaPilha);

// Insere k no topo da pilha em O(1).
void empilha(TipoPilha k, int saida, Pilha* minhaPilha);

// Remove o elemento que está no topo da pilha em O(1).
// Precondição: a pilha não pode estar vazia.
void desempilha(Pilha* minhaPilha);

// Libera a memória alocada para a pilha em O(n), onde n = size_.
void liberaPilha(Pilha* minhaPilha);

void imprimePilha(Pilha* minhaPilha);

#endif  // PILHA_H_
