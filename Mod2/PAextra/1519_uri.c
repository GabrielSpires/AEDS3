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

void copiaPalavra(Chave k, lista* origem, lista* dest){
  Node* node = procura(k, origem);
  Node* novoNode = malloc(sizeof(Node));
  novoNode->key = node->key;
  novoNode->keyAbreviada = node->keyAbreviada;

  novoNode->prev = prev(final(dest));
  novoNode->next = final(dest);
  final(dest)->prev->next = novoNode;
  final(dest)->prev= novoNode;
  dest->tamanho++;
}

void inserir(Chave k, lista* s) {
  Node* x = inicio(s);
  while (x != final(s) && strlen(key(x)) > strlen(k)) {
    x = next(x);
  }
  if(x != final(s) && strcmp(x->key, k) == 0){
    x->economia += (strlen(k)-2);
  }else if (x == final(s) || strcmp(key(x), k) != 0){
    Node* node = malloc(sizeof(Node));
    node->key = (char*)malloc(strlen(k)+1 * sizeof(char));
    node->keyAbreviada = (char*)malloc(strlen(k)+1 * sizeof(char));
    strcpy(node->key, k);
    strcpy(node->keyAbreviada, k);
    node->abreviar = 0;
    node->economia = strlen(k) - 2;
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


int main(int argc, char const *argv[]){
	int i = 0, n = 0; //Numero de palavras abreviadas
	char palavra[31], separador;
	lista palavras[27];

	do{
		for(i=0; i<27; i++) criaLista(&palavras[i]);
		
		do{
			scanf("%s%c", palavra, &separador);
			if(palavra[0] == '.') break;
			inserir(palavra, &palavras[palavra[0]%97]);
			copiaPalavra(palavra, &palavras[palavra[0]%97], &palavras[26]);
			// printf("%s ", palavra);
		}while(separador == ' ');
		// printf("\n");
		if(palavra[0] == '.') break;

		iterador j, k;
		int maiorEconomia = 0;
		for(i=0; i<26; i++){
			for(j = inicio(&palavras[i]); j != final(&palavras[i]); j=next(j)){
				if(j->economia > maiorEconomia){
					maiorEconomia = j->economia;
					k = j;
				}
			}
			for(j = inicio(&palavras[i]); j != final(&palavras[i]); j=next(j)){
				if(j->economia == maiorEconomia){
					if(strlen(j->key) > 2){
						j->keyAbreviada[1] = '.';
						j->keyAbreviada[2] = '\0';
						j->abreviar = 1;
						n++;
						break;
					}
				}
			}
			// printf("%d: %d\n", i, maiorEconomia);

			maiorEconomia = 0;
		}

		for(j = inicio(&palavras[26]); j != final(&palavras[26]); j=next(j)){
			printf("%s", j->keyAbreviada);
			if(next(j) != final(&palavras[26])) printf(" ");
		}
		if(inicio(&palavras[26]) != final(&palavras[26])){
			printf("\n");
		}

		printf("%d\n", n);
		for(i=0; i<26; i++){
			for(j = inicio(&palavras[i]); j != final(&palavras[i]); j=next(j)){
				if(j->abreviar == 1)
					printf("%s = %s\n", j->keyAbreviada, j->key);
			}
		}

		n = 0;
		for(i=0; i<27; i++) liberaLista(&palavras[i]);
	}while(1);

	return 0;
}