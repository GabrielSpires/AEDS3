#include "lista.h"

void criaLista(lista* s){
  s->tamanho = 0;
  s->final = malloc(sizeof(Node));
  s->final->next = s->final;
  s->final->prev = s->final;
}

int listaVazia(lista* s){
  return s->tamanho == 0;
}

int tamanhoLista(lista* s){
  return s->tamanho;
}

iterador inicioLista(lista* s){
  return s->final->next;
}

iterador finalLista(lista* s){
  return s->final;
}

iterador nextLista(iterador x){
  return x->next;
}

iterador prevLista(iterador x){
  return x->prev;
}

Chave keyLista(iterador x){
  return x->key;
}

iterador procuraLista(Chave k, lista* s){
  iterador i;
  for (i = inicioLista(s); i != finalLista(s); i = nextLista(i)){
    if (keyLista(i) == k){
      return i;
    } else if (keyLista(i) > k){
      return finalLista(s);
    }
  }
  return finalLista(s);
}

void inserirLista(Chave k, ChaveProb prob, lista* s){
  Node* x = inicioLista(s);
  while (x != finalLista(s) && x->probFogo < prob){
    x = nextLista(x);
  }
  if (x == finalLista(s) || keyLista(x) != k){
    Node* node = malloc(sizeof(Node));
    node->key = k;
    node->probFogo = prob;
    node->prev = prevLista(x);
    node->next = x;
    x->prev->next = node;
    x->prev = node;
    s->tamanho++;
  }
}

void apagaNode(Chave k, lista* s){
  Node* x = procuraLista(k, s);
  if (x != finalLista(s)){
    x->prev->next = x->next;
    x->next->prev = x->prev;
    free(x);
    s->tamanho--;
  }
}

void limparLista(lista* s){
  while (!listaVazia(s)){
    apagaNode(keyLista(inicioLista(s)), s);
  }
}

void liberaLista(lista* s){
  limparLista(s);
  free(s->final);
}
