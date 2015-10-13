#include "heap.h"
#define INF 1.0/0.0

void dijkstra(lista* verts, int origem, int numQuarts, int *vertsValidos){
	int i = 0;
	Heap meuHeap;
	iterador getNodo;
	short int* caminho = (short int*)calloc(numQuarts, sizeof(short int));
	int *posHeap = (int*)calloc(numQuarts, sizeof(int));
	int* distancias = (int*)calloc(numQuarts, sizeof(int)); //Vetor que guarda a distancia do ponto de saida ate cada quarteirao
	double *probs = (double*)malloc(numQuarts * sizeof(double));
	
	for(i=0; i<numQuarts; i++){ //Seta todas as distancias como infinito
		distancias[i] = INF;
		caminho[i] = -1;
		posHeap[i] = -1;
		probs[i] = 0;
	}
	distancias[origem] = 0;
	
	insereHeap(&meuHeap, 0, origem, posHeap);

	for (i = origem, getNodo = inicioLista(&verts[i]); getNodo != finalLista(&verts[i]); getNodo = nextLista(getNodo)){	
		if(vertsValidos[getNodo->key] == 1 && posHeap[getNodo->key] == -1){
			insereHeap(&meuHeap, (1-getNodo->probFogo)*(1-probs[i]), getNodo->key, posHeap);
			probs[getNodo->key] = (1-getNodo->probFogo)*(1-probs[i]);
		}
	}

	for(i=0; i<numQuarts-1; i++){
		/* código */
	}
}

void eliminaQuarts(lista *verts, int k, int bomb, int *vertsValidos){
	iterador getNodo;
	Fila f;
	criaFila(&f);
	int i = bomb;
	vertsValidos[bomb] = 1;
	enfileirar(bomb, &f, -1);

	while(!filaVazia(&f)){
		if(distPai(&f) < k){
			for (getNodo = inicioLista(&verts[i]); getNodo != finalLista(&verts[i]); getNodo = nextLista(getNodo)){
				// if(vertsValidos[getNodo->key] != 1){
				enfileirar(getNodo->key, &f, distPai(&f));
				vertsValidos[getNodo->key] = 1;
				// }
			}
		}
		desenfileirar(&f);
		i = frenteFila(&f);
	}
}

// double calcProbIncendio(){

// }

int main(){
	int i = 0, j = 0;
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
	int *vertsValidos = NULL;

	lista *verts = NULL;

	scanf("%d", &n);
	while(n--){
		scanf("%d %d %d %d %d %d", &q, &r, &s, &c, &k, &d);
		bomb = (int*)calloc(d, sizeof(int));
		verts = (lista*)malloc(q * sizeof(lista));
		vertsValidos = (int*)calloc(q, sizeof(int));
		for(i=0; i<q; i++) criaLista(&verts[i]);//Alocaçao dos vetores referentes a 'q' e 'd'

		while(r--){
			scanf("%d %d %lf", &x, &y, &probFogo);
			inserirLista(y, probFogo, &verts[x]);
			inserirLista(x, probFogo, &verts[y]);
		}
		for(y=0; y<d; y++){
			scanf("%d", &bomb[y]);
		}
		iterador getNodo;
		for(i=0; i<q; i++){
			printf("%d: ", i);
			for (getNodo = inicioLista(&verts[i]); getNodo != finalLista(&verts[i]); getNodo = nextLista(getNodo)){
	  			printf("%d(%.2lf) ", getNodo->key, getNodo->probFogo);
	  		}
	  		if(inicioLista(&verts[i]) == finalLista(&verts[i])){
	  			printf("vazio");
	  		}
	  		printf("\n");
		}//Printa as listas

		printf("\nBombs: ");
		for(i=0; i<d; i++){
			printf("%d ", bomb[i]);
		}
		printf("\n");//Printa os bombs

		//Elimina os quarteiroes que nao podem ser visitados
		for(i=0; i<d; i++){
			eliminaQuarts(verts, k, bomb[i], vertsValidos);
		}
		for(j=0; j<q; j++){
			printf("%d ", vertsValidos[j]);
		}printf("\n");
		

		for(i=0; i<q; i++) liberaLista(&verts[i]);
		free(verts);
		free(bomb);//Libera as listas
		free(vertsValidos);
	}

	return 0;
}