#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char* Chave;

typedef struct node{
  Chave key;
  Chave keyAbreviada;
  int abreviar;
  int economia;
  struct node* prev;
  struct node* next;
} Node;

typedef struct {
  Node* final;
  int tamanho;
} lista;

typedef Node* iterador;

void criaLista(lista* s);

int listaVazia(lista* s);

int tamanho(lista* s);

iterador inicio(lista* s);

iterador final(lista* s);

iterador next(iterador x);

iterador prev(iterador x);

Chave key(iterador x);

iterador procura(Chave k, lista* s);

void copiaPalavra(Chave k, lista* origem, lista* dest);

void inserir(Chave k, lista* s);

void apaga(Chave k, lista* s);

void limpar(lista* s);

void liberaLista(lista* s);
