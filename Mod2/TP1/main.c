#include "heap.h"
#define INF 1.0/0.0

void dijkstra(lista* verts, int origem, int numQuarts, int *vertsValidos, int c){
	int i = 0; //Variavel de controle
	Heap meuHeap; //Heap usado para saber a menor probabilidade de incendio a ser usada no algoritmo
	iterador getNodo; //Iterador do tipo Nodo usado pra percorrer a lista
	short int* caminho = (short int*)calloc(numQuarts, sizeof(short int));
	int *posHeap = (int*)calloc(numQuarts, sizeof(int)); //Vetor de posiçao que guarda onde no heap esta um vertice
	int *distancias = (int*)calloc(numQuarts, sizeof(int)); //Vetor que guarda a distancia do ponto de saida ate cada quarteirao
	int *visitados = (int*)calloc(numQuarts, sizeof(int)); //Vetor usado pra verificar quais os vertices sairam do heap (ja foram visitados)
	double *probs = (double*)malloc(numQuarts * sizeof(double));
	
	constroiHeap(&meuHeap, numQuarts);

	for(i=0; i<numQuarts; i++){ //Seta todas as distancias como infinito
		distancias[i] = INF;
		caminho[i] = -1;
		posHeap[i] = -1;
		probs[i] = 0;
	}
	distancias[origem] = 0;
	
	// insereHeap(&meuHeap, INF, origem, posHeap);

	while(meuHeap.sizeHeap >= 0){
		for (i = origem, getNodo = inicioLista(&verts[i]); getNodo != finalLista(&verts[i]); getNodo = nextLista(getNodo)){	
			double novaProb = (1-getNodo->probFogo)*(1-probs[i]);
			if(vertsValidos[getNodo->key] == 1 && posHeap[getNodo->key] == -1){
				insereHeap(&meuHeap, novaProb, getNodo->key, posHeap);
				probs[getNodo->key] = novaProb;
			}
			else{
				if(vertsValidos[getNodo->key] == 1 && meuHeap.vetor[getNodo->key].probFogo < novaProb){ //Atualiza a probabilidade do caminho
					meuHeap.vetor[getNodo->key].probFogo = novaProb; //O valor da probabilidade do vertice atual eh atualizado
					probs[getNodo->key] = novaProb; 
					refazBaixoCima(&meuHeap, posHeap); //Reorganiza o Heap de baixo pra cima (MaxHeap)
				}
			}
			int j;
			for(j=0; j <= meuHeap.sizeHeap; j++){
				printf("%.1lf ", meuHeap.vetor[j].probFogo);
			}
		}
		i = retiraHeap(&meuHeap, posHeap);
		printf("RET: %d\n", i);
		visitados[i] = 1;
	}
	printf("\nProb: %lf\n", 1.0-probs[c]);

	free(posHeap);
	free(probs);
	free(distancias);
	free(caminho);
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
	//Desaloca a fila
	liberaFila(&f);
}

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
		//Entrada das variaveis
		scanf("%d %d %d %d %d %d", &q, &r, &s, &c, &k, &d);
		//Alocaçao dos vetores referentes a 'q' e 'd'
		bomb = (int*)calloc(d, sizeof(int));
		verts = (lista*)malloc(q * sizeof(lista));

		//Aloca um vetor para guardar os vertices que podem ser visitados
		vertsValidos = (int*)calloc(q, sizeof(int));

		//Cria a lista de adjacencia
		for(i=0; i<q; i++) criaLista(&verts[i]);

		while(r--){
			scanf("%d %d %lf", &x, &y, &probFogo); //Recebe a entrada (aresta com probabilidade)
			inserirLista(y, probFogo, &verts[x]); //Insere a aresta na lista de adjacencia
			inserirLista(x, probFogo, &verts[y]); //Insere a aresta de volta (grafo nao direcionado)
		}
		for(y=0; y<d; y++){
			scanf("%d", &bomb[y]); //Recebe o numero dos vertices que tem bombeiro
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

		//Elimina os quarteiroes que nao podem ser visitados (busca em largura)
		//A busca eh feita a partir de cada vertice com corpo de bombeiros
		for(i=0; i<d; i++) eliminaQuarts(verts, k, bomb[i], vertsValidos);

		for(j=0; j<q; j++){
			printf("%d ", vertsValidos[j]);
		}printf("\n"); //printa os vertices que podem ser alcançados


		dijkstra(verts, s, q, vertsValidos, c);


		//Desalocaçao de memoria		
		for(i=0; i<q; i++) liberaLista(&verts[i]);
		free(verts);
		free(bomb);
		free(vertsValidos);
	}

	return 0;
}