#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int Chave;
typedef double ChaveProb;

typedef struct node{
  Chave key;
  ChaveProb probFogo;
  ChaveProb distOrigem;
  struct node* prev;
  struct node* next;
}Node;

typedef struct{
  Node* final;
  int tamanho;
}lista;

typedef Node* iterador;

void criaLista(lista* s);

int listaVazia(lista* s);

int tamanhoLista(lista* s);

iterador inicioLista(lista* s);

iterador finalLista(lista* s);

iterador nextLista(iterador x);

iterador prevLista(iterador x);

Chave keyLista(iterador x);

iterador procuraLista(Chave k, lista* s);

void inserirLista(Chave k, ChaveProb prob, lista* s);

void apagaNode(Chave k, lista* s);

void limparLista(lista* s);

void liberaLista(lista* s);
