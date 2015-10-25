#include "heap.h"
#define INF 1.0/0.0

void dijkstra(lista* verts, int origem, int numQuarts, int *vertsValidos, int c){
	if(!vertsValidos[origem]){ //Testa se o vertice de chegada nao eh um vertice valido
		printf("-1\n");
		return;	//Caso o vertice de chegada seja invalido, sai da funçao
	}
	Heap meuHeap;
	constroiHeap(&meuHeap, numQuarts); //Cria o Heap
 
 	//Vetor que guarda o antecessor de cada vertice usado no caminho
 	int *antecessor  = (int*)	 malloc(numQuarts * sizeof(int));
 	//Vetor que guarda o caminho na ordem correta (saida -> chegada)
	int *caminho	 = (int*)	 malloc(numQuarts * sizeof(int));
	//Vetor que verifica que o vertice ja foi visitado (ja foi retirado do heap)
	int *visitado	 = (int*)	 calloc(numQuarts , sizeof(int));
	//Vetor que guarda as probabilidades de cada vertice
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
	iterador nodoAtual; //Iterador usado para percorrer a fila
	while(meuHeap.sizeHeap >= 0){ 
		visitado[i] = 1; //Seta o vertice removido do Heap como visitado
		for(nodoAtual = inicioLista(&verts[i]); nodoAtual != finalLista(&verts[i]); nodoAtual = nextLista(nodoAtual)){ 
			pN = (prob[i])*(1-nodoAtual->probFogo); //Probabilidade do vertice atual ate a origem
			if(visitado[nodoAtual->key] == 0 && vertsValidos[nodoAtual->key] == 1 && meuHeap.posHeap[nodoAtual->key] == -1){
				insereHeap(&meuHeap, pN, nodoAtual->key); //Insere o vertice atual no heap com Pn
				antecessor[nodoAtual->key] = i; //seta o antecessor dele como o vertice anterior
				prob[nodoAtual->key] = pN; //Coloca a probabilidade dele como Pn
			}
			else{
				if(visitado[nodoAtual->key] == 0 
					&& vertsValidos[nodoAtual->key] == 1 
					&& meuHeap.vetor[meuHeap.posHeap[nodoAtual->key]].probFogo < prob[i]*(1-nodoAtual->probFogo)){
						//Atualiza a prob
						prob[nodoAtual->key] = prob[i]*(1-nodoAtual->probFogo); 
						//Atualiza a probabilidade no heap
						meuHeap.vetor[meuHeap.posHeap[nodoAtual->key]].probFogo = prob[i]*(1-nodoAtual->probFogo);
						//Refaz o Heap
						refazBaixoCima(&meuHeap, meuHeap.posHeap[nodoAtual->key]);
						//seta o antecessor dele como o vertice anterior
						antecessor[nodoAtual->key] = i;
				}
			}
		}
		i = retiraHeap(&meuHeap);
	}
	//Testa se a probabilidade eh infinita, se for printa -1
	//Printa a probabilidade e o caminho
	j=1;
	if(1.0-prob[c] == INF) printf("-1\n");
	else{
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
					visitado[nodoAtual->key] = 1; //Seta o vertice atual como visitado
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
		
		//Elimina os quarteiroes que nao podem ser visitados (busca em largura)
		//A busca eh feita a partir de cada vertice com corpo de bombeiros
		for(i=0; i<d; i++) eliminaQuarts(verts, k, bomb[i], vertsValidos, q);

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