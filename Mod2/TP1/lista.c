#include "lista.h"

int cmp(const void* a, const void* b){
  return *(char*)a - *(char*)b;
}

int cmpInt(const void* a, const void* b){
  return *(int*)a - *(int*)b;
}

void criaLista(lista* s){
  s->tamanho = 0;
  s->final = malloc(sizeof(Node));
  s->final->next = s->final;
  s->final->prev = s->final;
}

int listaVazia(lista* s){
  return s->tamanho == 0;
}

int tamanho(lista* s){
  return s->tamanho;
}

iterador inicio(lista* s){
  return s->final->next;
}

iterador final(lista* s){
  return s->final;
}

iterador next(iterador x){
  return x->next;
}

iterador prev(iterador x){
  return x->prev;
}

Chave key(iterador x){
  return x->key;
}

iterador procura(Chave k, lista* s){
  iterador i;
  for (i = inicio(s); i != final(s); i = next(i)){
    if (key(i) == k){
      return i;
    } else if (key(i) > k){
      return final(s);
    }
  }
  return final(s);
}

void inserir(Chave k, ChaveProb prob, lista* s){
  Node* x = inicio(s);
  while (x != final(s) && x->probFogo < prob){
    x = next(x);
  }
  if (x == final(s) || key(x) != k){
    Node* node = malloc(sizeof(Node));
    node->key = k;
    node->probFogo = prob;
    node->prev = prev(x);
    node->next = x;
    x->prev->next = node;
    x->prev = node;
    s->tamanho++;
  }
}

void apaga(Chave k, lista* s){
  Node* x = procura(k, s);
  if (x != final(s)){
    x->prev->next = x->next;
    x->next->prev = x->prev;
    free(x);
    s->tamanho--;
  }
}

void limpar(lista* s){
  while (!listaVazia(s)){
    apaga(key(inicio(s)), s);
  }
}

void liberaLista(lista* s){
  limpar(s);
  free(s->final);
}
