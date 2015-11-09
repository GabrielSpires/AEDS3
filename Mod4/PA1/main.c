#include "pilha.h"

//criar um vetor com a saida ordenada
//comparar com a saida do topo da pilha
int main(int argc, char const *argv[]){
  Pilha minhaPilha;

  int n, //n° de motoristas
	  k, //capacidade do estacionamento
	  c, //horario de chegada
	  s, //horario de saida
	  *saidas = NULL; //vetor com os horarios de saida

  scanf("%d %d", &n, &k);
  while(n && k){
  	criaPilha(&minhaPilha);
  	saidas = (int*)malloc(k * sizeof(int));
  	
  	while(n--){
  		scanf("%d %d", &c, &s);
  		empilha(c, s, &minhaPilha);
  	}

  	imprimePilha(&minhaPilha);
  	liberaPilha(&minhaPilha);
  	free(saidas);
  	scanf("%d %d", &n, &k);
  }
  
  return 0;
}