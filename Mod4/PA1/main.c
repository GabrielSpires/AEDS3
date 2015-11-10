#include <stdio.h>
#include <stdlib.h>

// Tipo dos elementos na pilha.
typedef int TipoPilha;

// Define como os elementos da pilha serão organizados na memória.
typedef struct nodePilha{
  TipoPilha cheg;
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

int main(int argc, char const *argv[]){
  Pilha minhaPilha;

	int n, //n° de motoristas
	  	k, //capacidade do estacionamento
			c, //horario de chegada
			s, //horario de saida
	  	saidaAnt,
	  	aux = 1;

  scanf("%d %d", &n, &k);
  while(n && k){
  	aux = 1;
  	criaPilha(&minhaPilha);
  	
  	while(n--){
  		scanf("%d %d", &c, &s);
  		saidaAnt = 0;
  		while(tamPilha(&minhaPilha) > 0 && c >= topoPilha(&minhaPilha)){
  			if(topoPilha(&minhaPilha) >= saidaAnt && aux) aux = 1; //Sim
  			else aux = 0; //Nao
  			saidaAnt = topoPilha(&minhaPilha);
  			desempilha(&minhaPilha);
  		}

  		if(tamPilha(&minhaPilha) < k && aux) aux = 1; //Sim
  		else aux = 0; //Nao
  		empilha(c, s, &minhaPilha);
  	}

  	saidaAnt = 0;
  	while(tamPilha(&minhaPilha) > 0){
  		if(topoPilha(&minhaPilha) >= saidaAnt && aux) aux = 1;
			else aux = 0;
			saidaAnt = topoPilha(&minhaPilha);
			desempilha(&minhaPilha);
  	}

  	if(aux) printf("Sim\n");
  	else printf("Nao\n");
  	liberaPilha(&minhaPilha);
  	scanf("%d %d", &n, &k);
  }
  
  return 0;
}

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
  return minhaPilha->end->next->saida;
}

void empilha(TipoPilha k, int saida, Pilha* minhaPilha) {
  // Ponteiro para o primeiro elemento na pilha.
  NodePilha* primeiro = minhaPilha->end->next;
  // Cria um novo nó e define o valor dos seus campos.
  NodePilha* novoNode = malloc(sizeof(NodePilha));
  novoNode->cheg = k;
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