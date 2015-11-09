#include "pilha.h"

void criaPilha(Pilha* minhaPilha) {
  minhaPilha->tamanho = 0;
  minhaPilha->end = malloc(sizeof(NodePilha));
  minhaPilha->end->next = minhaPilha->end;
  minhaPilha->end->prev = minhaPilha->end;
}

int pilhaVazia(Pilha* minhaPilha) {
  return minhaPilha->tamanho == 0;
}

int tamPilha(Pilha* minhaPilha) {
  return minhaPilha->tamanho;
}

TipoPilha topoPilha(Pilha* minhaPilha) {
  return minhaPilha->end->next->chave;
}

void empilha(TipoPilha k, int saida, Pilha* minhaPilha) {
  // Ponteiro para o primeiro elemento na pilha.
  NodePilha* primeiro = minhaPilha->end->next;
  // Cria um novo nó e define o valor dos seus campos.
  NodePilha* novoNode = malloc(sizeof(NodePilha));
  novoNode->chave = k;
  novoNode->saida = saida;
  novoNode->prev = primeiro->prev;
  novoNode->next = primeiro;
  // Ajusta o valor dos ponteiros dos nos adjacentes ao novo nó.
  primeiro->prev->next = novoNode;
  primeiro->prev = novoNode;
  minhaPilha->tamanho++;
}

void desempilha(Pilha* minhaPilha) {
  NodePilha* primeiro = minhaPilha->end->next;  // Ponteiro para o primeiro elemento na pilha.
  primeiro->prev->next = primeiro->next;
  primeiro->next->prev = primeiro->prev;
  free(primeiro);
  minhaPilha->tamanho--;
}

void liberaPilha(Pilha* minhaPilha) {
  while (!pilhaVazia(minhaPilha)) {
    desempilha(minhaPilha);  // A função pop() libera a memórima de cada nó removido da pilha.
  }
  free(minhaPilha->end);
}

void imprimePilha(Pilha* minhaPilha){
  IteradorPilha i;
  for(i = minhaPilha->end->prev; i != minhaPilha->end; i = i->prev){
    printf("%d ", i->chave);
  }
  printf("\n");
}