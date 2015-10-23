#include "heap.h"
#define INF 1.0/0.0

void dijkstra(lista* verts, int origem, int numQuarts, int *vertsValidos, int c){
	if(!vertsValidos[origem]){
		printf("-1\n");
		return;
	}
	Heap meuHeap;
	constroiHeap(&meuHeap, numQuarts);
 

 	int *antecessor  = (int*)	 malloc(numQuarts * sizeof(int));
	int *caminho	 = (int*)	 malloc(numQuarts * sizeof(int));
	int *visitado	 = (int*)	 calloc(numQuarts , sizeof(int));
	double *prob	 = (double*) malloc(numQuarts * sizeof(double));

	double pN;
	int i, j = 1;
	for(i=0; i<=numQuarts; i++) meuHeap.posHeap[i] = -1;
	for(i=0; i<numQuarts; i++){
		antecessor[i] = -1;
		caminho[i]	  = -1;
		prob[i] 	  = -INF;
	}
	prob[origem] = 1; //A chance de nao pegar fogo no vertice de saida eh de 100%
	i = origem;
	iterador nodoAtual;
	int printar = 0;
	while(meuHeap.sizeHeap >= 0){
		visitado[i] = 1;
		for(nodoAtual = inicioLista(&verts[i]); nodoAtual != finalLista(&verts[i]); nodoAtual = nextLista(nodoAtual)){
			if(printar == 1) printf("prob[i] = %lf\n", prob[i]);
			if(printar == 1) printf("NodoAtual: %d\n", nodoAtual->key);
			pN = (prob[i])*(1-nodoAtual->probFogo); //PN (0, 3, 4) = (PN (0, 3) ∗ PN (3, 4))
			if(printar == 1) printf("pN = %.2lf*%.2lf\n", (prob[i]), (1-nodoAtual->probFogo));
			if(visitado[nodoAtual->key] == 0 && vertsValidos[nodoAtual->key] == 1 && meuHeap.posHeap[nodoAtual->key] == -1){
				if(printar == 1) printf("+Inseriu: %d -> ProbN = %.2lf\n", nodoAtual->key, pN);
				insereHeap(&meuHeap, pN, nodoAtual->key);
				antecessor[nodoAtual->key] = i;
				prob[nodoAtual->key] = pN;
			}
			else{
				if(visitado[nodoAtual->key] == 0 && vertsValidos[nodoAtual->key] == 1 
				&&	meuHeap.vetor[meuHeap.posHeap[nodoAtual->key]].probFogo < prob[i]*(1-nodoAtual->probFogo)){
				if(printar == 1) printf("ELSE %d\n", nodoAtual->key);
				if(printar == 1) printf("ELSE posHeap: %d\n", meuHeap.posHeap[nodoAtual->key]);
				if(printar == 1) printf("ELSE visitado: %d\n", visitado[nodoAtual->key]);
				if(printar == 1) printf("ELSE validos: %d\n", vertsValidos[nodoAtual->key]);
				if(printar == 1) printf("ELSE probs: %.2lf < %.2lf ?\n", meuHeap.vetor[meuHeap.posHeap[nodoAtual->key]].probFogo, prob[i]*(1-nodoAtual->probFogo));
				if(printar == 1) printf(">> ENTROU NO ELSE IF <<\n");
					prob[nodoAtual->key] = prob[i]*(1-nodoAtual->probFogo);
					meuHeap.vetor[meuHeap.posHeap[nodoAtual->key]].probFogo = prob[i]*(1-nodoAtual->probFogo);
				if(printar == 1) printf("Nova Prob do vertice %d: %.2lf\n", meuHeap.vetor[meuHeap.posHeap[nodoAtual->key]].quarteirao, meuHeap.vetor[meuHeap.posHeap[nodoAtual->key]].probFogo);
					refazBaixoCima(&meuHeap, meuHeap.posHeap[nodoAtual->key]);
					antecessor[nodoAtual->key] = i;
				}
			}
		}
		
		if(printar == 1) printf("Heap -> [");
		if(printar == 1) for(j=1; j <= meuHeap.sizeHeap; j++) printf("%d(%.2lf) ", meuHeap.vetor[j].quarteirao, meuHeap.vetor[j].probFogo);
		if(printar == 1) printf("\b]\n");
		i = retiraHeap(&meuHeap);
		if(printar == 1) printf("-Retirou: %d pN = %.2lf\n\n", i, prob[i]);
		//visitado[i] = 1;

	}
	// for(i=0; i<numQuarts; i++){
	// 	printf("%d(%.2lf), ", i, prob[i]);
	// }printf("\b\b\n");
	j=1;
	if(1.0-prob[c] == INF) printf("-1\n");
	else{
		// printf(">> ");
		// for(i=0; i<numQuarts; i++){
		// 	printf("%d ", antecessor[i]);
		// }printf("\n");
		printf("%.2lf", 1.0-prob[c]);

		caminho[0] = c;

		for(i = c; i != origem;){
			caminho[j++] = antecessor[i];
			i = antecessor[i];
		}caminho[j] = origem;

		for(i=j-1; i>=0; i--){
			printf(" %d", caminho[i]);
		}printf("\n");
	}

	free(caminho);
	free(prob);
	free(antecessor);
	free(visitado);
	liberaHeap(&meuHeap);
}

void eliminaQuarts(lista *verts, int k, int bomb, int *vertsValidos, int q){
	iterador nodoAtual; //Variavel do tipo iterador(Nodo) usada para percorrer a lista
	Fila f; //Fila usada na busca em largura
	criaFila(&f); //Cria a fila vazia
	int i = bomb; //A variavel i recebe o numero do vertice que tem corpo de bombeiros
	vertsValidos[bomb] = 1; //Seta o vertice inicial como valido
	enfileirar(bomb, &f, 0); //Enfileira o vertice inicial com distancia zero
	int *visitado = (int*) calloc(q,sizeof(int));

	while(!filaVazia(&f)){ //Faz a busca enquanto a fila aind conter vertices
		if(distPai(&f) < k){ //So faz a busca nos vertices que estao dentro da distancia limite
			for(nodoAtual = inicioLista(&verts[i]); nodoAtual != finalLista(&verts[i]); nodoAtual = nextLista(nodoAtual)){
				if(!visitado[nodoAtual->key]){
					enfileirar(nodoAtual->key, &f, distPai(&f)+1); //Enfileira o vertice incrementando a distancia do pai
					visitado[nodoAtual->key] = 1;
				}
				vertsValidos[nodoAtual->key] = 1; //Seta o vertice visitado como valido (esta dentro da distancia limite)
			}
		}
		desenfileirar(&f); //Depois de enfileirar todos os vertices adjacentes, o vertice visitado eh removido da fila
		i = frenteFila(&f); //Seta a variavel i com o numero do vertice que esta na frente da fila (proximo a visitar)
	}
	free(visitado);//Desaloca a fila
	liberaFila(&f); //Desaloca a fila
}

int main(){
	int i;
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

		//Aloca um vetor para guardar os vertices que podem ser percorridos
		vertsValidos = (int*)calloc(q, sizeof(int));

		//Cria a lista de adjacencias
		for(i=0; i<q; i++) criaLista(&verts[i]);

		while(r--){
			scanf("%d %d %lf", &x, &y, &probFogo); //Recebe a entrada (aresta com probabilidade)
			inserirLista(y, probFogo, &verts[x]); //Insere a aresta na lista de adjacencia
			inserirLista(x, probFogo, &verts[y]); //Insere a aresta de volta (grafo nao direcionado)
		}
		for(y=0; y<d; y++){
			scanf("%d", &bomb[y]); //Recebe o numero dos vertices que tem bombeiro
		}
		/*
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
		*/
		//Elimina os quarteiroes que nao podem ser visitados (busca em largura)
		//A busca eh feita a partir de cada vertice com corpo de bombeiros
		for(i=0; i<d; i++) eliminaQuarts(verts, k, bomb[i], vertsValidos, q);

		// for(j=0; j<q; j++){
		// 	printf("%d ", vertsValidos[j]);
		// }printf("\n"); //printa os vertices que podem ser alcançados
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