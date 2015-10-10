#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int Chave;

typedef struct node{
  Chave key;
  struct node* prev;
  struct node* next;
} Node;

typedef struct {
  Node* final;
  int tamanho;
} lista;

typedef Node* iterador;

int cmp(const void* a, const void* b);
int cmpInt(const void* a, const void* b);

void criaLista(lista* s);

int listaVazia(lista* s);

int tamanho(lista* s);

iterador inicio(lista* s);

iterador final(lista* s);

iterador next(iterador x);

iterador prev(iterador x);

Chave key(iterador x);

iterador procura(Chave k, lista* s);

void inserir(Chave k, lista* s);

void apaga(Chave k, lista* s);

void limpar(lista* s);

void liberaLista(lista* s);
