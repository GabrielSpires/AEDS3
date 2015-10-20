#include "fila.h"

void criaFila(Fila* q){
  q->size = 0;
  q->end = malloc(sizeof(NodeFila));
  q->end->next = q->end;
  q->end->prev = q->end;
}

int filaVazia(Fila* q){
  return q->size == 0;
}

int tamFila(Fila* q){
  return q->size;
}

TipoFila frenteFila(Fila* q){
  return q->end->next->key;
}

int distPai(Fila* q){
  return q->end->next->distBomb;
}

TipoFila fundoFila(Fila* q){
  return q->end->prev->key;
}

void enfileirar(TipoFila k, Fila* q, int distBomb){
  // Cria um novo nó e define o valor dos seus campos.
  NodeFila* node = malloc(sizeof(NodeFila));
  node->distBomb = distBomb;
  node->key = k;
  node->prev = q->end->prev;
  node->next = q->end;
  // Ajusta o valor dos ponteiros dos nós adjacentes ao novo nó.
  q->end->prev->next = node;
  q->end->prev = node;
  q->size++;
}

void desenfileirar(Fila* q){
  NodeFila* first = q->end->next;  // Ponteiro para o primeiro elemento na fila.
  first->prev->next = first->next;
  first->next->prev = first->prev;
  free(first);
  q->size--;
}

// void copy(Fila* p, Fila* q){
//   // Apaga todos os elementos na fila corrente.
//   while (!filaVazia(p)){
//     desenfileirar(p);
//   }
//   // Insere os elementos de q em p.
//   NodeFila* i = NULL;
//   for (i = q->end->next; i != q->end; i = i->next){
//     enfileirar(i->key, p, i->distBomb);
//   }
// }

void imprimeFila(Fila* q){
  NodeFila* i = NULL;
  for (i = q->end->next; i != q->end; i = i->next){
    printf("%d %d\n", i->key, i->distBomb);
  }
}

void liberaFila(Fila* q){
  // Primeiramente, remove todos os elementos da fila.
  while (!filaVazia(q)) {
    desenfileirar(q);  // A função desenfileirar() libera a memórima de cada nó removido da fila;
  }
  // Em seguida, libera a memória alocada ao sentinela.
  free(q->end);
}