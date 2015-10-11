#define INF 1.0/0.0

#include "lista.h"
#include "fila.h"
#include "heap.h"

// void dijkstra(lista* verts, int origem, int numQuarts){
// 	int i = 0;
// 	short int* camMin = (short int*)calloc(numQuarts, sizeof(short int));
// 	int* distancias = (int*)calloc(numQuarts, sizeof(int)); //Vetor que guarda a distancia do ponto de saida ate cada quarteirao
	
// 	for(i=0; i<numQuarts; i++) //Seta todas as distancias como infinito
// 		distancias[i] = INF;

// 	distancias[origem] = 0;

// 	for(i=0; i<numQuarts-1; i++){
// 		/* código */
// 	}
// }

// double calcProbIncendio(){

// }

int main(){
	int i = 0;
	int x = 0, //id do quarteirao
		y = 0, //id do outro quarteirao
		n = 0, //n° de testes
		q = 0, //n° de quarteiroes
		r = 0, //n° de ruas
		s = 0, //ponto de saida
		c = 0, //ponto de chegada
		k = 0, //distancia de um corpo de bomb.
		d = 0, //numero de corpos de bombeiro na cidade
		*bomb = NULL; //Vetor que guarda quais quarteiroes tem corpo de bombeiros
	double probFogo = 0;

	lista* verts = NULL;

	scanf("%d", &n);
	while(n--){
		scanf("%d %d %d %d %d %d", &q, &r, &s, &c, &k, &d);
		bomb = (int*)calloc(d, sizeof(int));
		verts = (lista*)malloc(q * sizeof(lista));
		for(i=0; i<q; i++) criaLista(&verts[i]);//Alocaçao dos vetores referentes a 'q' e 'd'

		while(r--){
			scanf("%d %d %lf", &x, &y, &probFogo);
			inserir(y, probFogo, &verts[x]);
			inserir(x, probFogo, &verts[y]);
		}
		y = d; //Preservo o valor de d pra saber o tamanho do vetor depois
		while(d--){
			scanf("%d", &bomb[d]);
		}
		iterador getNodo;
		for(i=0; i<q; i++){
			printf("%d: ", i);
			for (getNodo = inicio(&verts[i]); getNodo != final(&verts[i]); getNodo = next(getNodo)){
	  			printf("%d(%.2lf) ", getNodo->key, getNodo->probFogo);
	  		}
	  		if(inicio(&verts[i]) == final(&verts[i])){
	  			printf("vazio");
	  		}
	  		printf("\n");	
		}//Printa as listas

		printf("Bombs: ");
		for(i=0; i<y; i++){
			printf("%d ", bomb[i]);
		}
		printf("\n");//Printa os bombs

		for(i=0; i<q; i++) liberaLista(&verts[i]);
		free(verts);
		free(bomb);//Libera as listas
	}
	// printf("\n");
	// Fila minhaFila;
	// criaFila(&minhaFila);
	// enfileirar(10, &minhaFila);
	// enfileirar(50, &minhaFila);
	// enfileirar(30, &minhaFila);
	// enfileirar(25, &minhaFila);
	// imprimeFila(&minhaFila);
	// desenfileirar(&minhaFila);
	// imprimeFila(&minhaFila);
	// liberaFila(&minhaFila);

	// int teste[7] = {1, 3, 5, 2, 6, 8, 4};
	char teste[] = "_ordenas";
	int tamCoisa = strlen(teste)-1;
	for(i=0; i<=tamCoisa; i++) printf("%c ", teste[i]);
	printf("\n");

	// heapsort(&teste[0], tamCoisa);

	for(i=0; i<=tamCoisa; i++) printf("%c ", teste[i]);
	printf("\n");

	refazBaixoCima(&teste[0], tamCoisa);

	for(i=0; i<=tamCoisa; i++) printf("%c ", teste[i]);
	printf("\n");

	teste[1] = 'a';

	refazCimaBaixo(&teste[0], 1, tamCoisa);

	for(i=0; i<=tamCoisa; i++) printf("%c ", teste[i]);
	printf("\n");

	return 0;
}