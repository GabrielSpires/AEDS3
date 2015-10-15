#include "heap.h"
#define INF 1.0/0.0

void dijkstra(lista* verts, int origem, int numQuarts, int *vertsValidos, int c){
	int i = 0; //Variavel de controle
	Heap meuHeap; //Heap usado para saber a menor probabilidade de incendio a ser usada no algoritmo
	iterador nodoAtual; //Iterador do tipo Nodo usado pra percorrer a lista
	short int* caminho = (short int*)calloc(numQuarts, sizeof(short int));
	int *posHeap = (int*)calloc(numQuarts, sizeof(int)); //Vetor de posiçao que guarda onde no vetor do heap esta um vertice
	int *distancias = (int*)calloc(numQuarts, sizeof(int)); //Vetor que guarda a distancia do ponto de saida ate cada quarteirao
	int *visitados = (int*)calloc(numQuarts, sizeof(int)); //Vetor usado pra verificar quais os vertices sairam do heap (ja foram visitados)
	double *probs = (double*)malloc(numQuarts * sizeof(double)); //
	
	constroiHeap(&meuHeap, numQuarts);

	for(i=0; i<numQuarts; i++){
		distancias[i] = INF; //Seta todas as distancias como infinito
		caminho[i] = -1;
		posHeap[i] = -1;
		probs[i] = 0;
	}
	distancias[origem] = 0; //Seta a distancia para o vertice de origem como zero
	
	// insereHeap(&meuHeap, INF, origem, posHeap);
	i = origem;
	while(meuHeap.sizeHeap >= 0){
		for(nodoAtual = inicioLista(&verts[i]); nodoAtual != finalLista(&verts[i]); nodoAtual = nextLista(nodoAtual)){	
			double probN = (1-probs[i])*(1-nodoAtual->probFogo);
			if(vertsValidos[nodoAtual->key] == 1 && posHeap[nodoAtual->key] == -1){
				insereHeap(&meuHeap, probN, nodoAtual->key, posHeap);
				probs[nodoAtual->key] = probN;
			}
			else{
				if(vertsValidos[nodoAtual->key] == 1 && meuHeap.vetor[nodoAtual->key].probFogo < probN){ //Atualiza a probabilidade do caminho
					meuHeap.vetor[nodoAtual->key].probFogo = probN; //O valor da probabilidade do vertice atual eh atualizado
					probs[nodoAtual->key] = probN; 
					refazBaixoCima(&meuHeap, posHeap); //Reorganiza o Heap de baixo pra cima (MaxHeap)
				}
			}
			// int j;
			// for(j=0; j <= meuHeap.sizeHeap; j++) printf("%.1lf ", meuHeap.vetor[j].probFogo);
		}
		i = retiraHeap(&meuHeap, posHeap);
		// printf("RET: %d\n", i);
		visitados[i] = 1;
	}
	printf("\nProb: %lf\n", 1.0-probs[c]);

	free(posHeap);
	free(probs);
	free(distancias);
	free(caminho);
}

void eliminaQuarts(lista *verts, int k, int bomb, int *vertsValidos){
	iterador nodoAtual; //Variavel do tipo iterador(Nodo) usada para percorrer a lista
	Fila f; //Fila usada na busca em largura
	criaFila(&f); //Cria a fila vazia
	int i = bomb; //A variavel i recebe o numero do vertice que tem corpo de bombeiros
	vertsValidos[bomb] = 1; //Seta o vertice inicial como valido
	enfileirar(bomb, &f, 0); //Enfileira o vertice inicial com distancia zero

	while(!filaVazia(&f)){ //Faz a busca enquanto a fila aind conter vertices
		if(distPai(&f) < k){ //So faz a busca nos vertices que estao dentro da distancia limite
			for(nodoAtual = inicioLista(&verts[i]); nodoAtual != finalLista(&verts[i]); nodoAtual = nextLista(nodoAtual)){
				enfileirar(nodoAtual->key, &f, distPai(&f)+1); //Enfileira o vertice incrementando a distancia do pai
				vertsValidos[nodoAtual->key] = 1; //Seta o vertice visitado como valido (esta dentro da distancia limite)
			}
		}
		desenfileirar(&f); //Depois de enfileirar todos os vertices adjacentes, o vertice visitado eh removido da fila
		i = frenteFila(&f); //Seta a variavel i com o numero do vertice que esta na frente da fila (proximo a visitar)
	}
	//Desaloca a fila
	liberaFila(&f); //Desaloca a fila
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
	  			printf("isolado");
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

		//Acha o menor caminho possivel atraves dos vertices validos
		dijkstra(verts, s, q, vertsValidos, c); //DIJKSTRA

		//Desalocaçao de memoria
		for(i=0; i<q; i++) liberaLista(&verts[i]);
		free(verts);
		free(bomb);
		free(vertsValidos);
	}

	return 0;
}