#include "lista.h"

int cmp(const void* a, const void* b){
  return *(char*)a - *(char*)b;
}

int cmpInt(const void* a, const void* b){
  return *(int*)a - *(int*)b;
}

void criaLista(lista* s) {
  s->tamanho = 0;
  s->final = malloc(sizeof(Node));
  s->final->next = s->final;
  s->final->prev = s->final;
}

int listaVazia(lista* s) {
  return s->tamanho == 0;
}

int tamanho(lista* s){
  return s->tamanho;
}

iterador inicio(lista* s) {
  return s->final->next;
}

iterador final(lista* s) {
  return s->final;
}

iterador next(iterador x) {
  return x->next;
}

iterador prev(iterador x) {
  return x->prev;
}

Chave key(iterador x) {
  return x->key;
}

iterador procura(Chave k, lista* s) {
  iterador i;
  for (i = inicio(s); i != final(s); i = next(i)) {
    if (strcmp(key(i), k) == 0){
      return i;
    } else if (strcmp(key(i), k) > 0) {
      return final(s);
    }
  }
  return final(s);
}

void inserir(Chave k, lista* s) {
  Node* x = inicio(s);
  while (x != final(s) && strcmp(key(x), k) < 0) {
    x = next(x);
  }
  if(x != final(s) && strcmp(x->key, k) == 0){
    x->tam++;
  }else if (x == final(s) || strcmp(key(x), k) != 0){
    Node* node = malloc(sizeof(Node));
    node->tam = 1;
    node->key = (char*)malloc(strlen(k)+1 * sizeof(char));
    strcpy(node->key, k);
    node->prev = prev(x);
    node->next = x;
    x->prev->next = node;
    x->prev = node;
    s->tamanho++;
  }
}

void apaga(Chave k, lista* s) {
  Node* x = procura(k, s);
  if (x != final(s)) {
    x->prev->next = x->next;
    x->next->prev = x->prev;
    free(x);
    s->tamanho--;
  }
}

void limpar(lista* s) {
  while (!listaVazia(s)) {
    apaga(key(inicio(s)), s);
  }
}

void liberaLista(lista* s) {
  limpar(s);
  free(s->final);
}
