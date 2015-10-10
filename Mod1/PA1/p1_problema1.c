#include <stdio.h>
#include <stdlib.h>

//Adiciona 1 onde existe relaçao entre os nodos
void adicionaAresta(short int* matrixAdj[], int vOrig, int vDest);

//Algoritmo de busca em profundidade (Caminhamento pre-ordem)
int visitaDFS(int n, int v, short int* matrixAdj[], short int* visitado);

int main(){
	int t=0, //qtd de casos de teste t < 100
		n=0, //nodo inicial
		x=0, //largura do labirinto
		v=0, //vertices
		a=0, //arestas
		vOrig=0, //vertice de onde a linha parte
		vDest=0, //vertice em que a linha chega
		i=0,
		j=0,
		k=0;

	short int** matrixAdj = NULL;
	short int* visitado = NULL;
	
	// printf("# de testes: "); //PRINTF DESNECESSARIO!
	scanf("%d", &t); //qtd de testes

	for(k=0; k<t; k++){ //roda ate todos os testes serem feitos
		// printf("node inicial: "); //PRINTF DESNECESSARIO!
		scanf("%d", &n); //pto de partida
		// printf("# de vertices e arestas: "); //PRINTF DESNECESSARIO!
		scanf("%d", &v); //qtd de vertices
		scanf("%d", &a); //qtd de arestas

		//Aloca a matriz de adj e o vetor de visitados
		matrixAdj = (short int**)calloc(v, sizeof(short int*));
		for(i=0; i<v; i++){
			matrixAdj[i] = (short int*)calloc(v, sizeof(short int));
		}
		visitado = (short int*)calloc(v, sizeof(short int));

		//Recebe a localizaçao das linhas a serem traçadas
		//e preenche a matriz de acordo
		for(i=0; i<a; i++){
			// printf("aresta %d: ", i+1); //PRINTF DESNECESSARIO!
			scanf("%d %d", &vOrig, &vDest);
			adicionaAresta(&matrixAdj[0], vOrig, vDest);
		}

		//Print muito louco da "matriz"
		// printf("   ");
		// for(i=0; i<v; i++) printf(" %2d ", i);
		// printf("\n   +");
		// for(k=0; k<v; k++) printf("---+");
		// 	printf("\n");
		// for(i=0; i<v; i++){
		// 	printf("%2d |", i);
		// 	for(j=0; j<v; j++){
		// 		if(matrixAdj[i][j] != 0) printf("%2d |", matrixAdj[i][j]);
		// 		else printf("   |");
		// 	}printf("\n   +");
		// 	for(k=0; k<v; k++) printf("---+");
		// 	printf("\n");
		// }
		//Fim do print muito louco
		
		printf("%d\n", visitaDFS(n, v, matrixAdj, visitado));

		free(matrixAdj);
		free(visitado);
	}	
	return 0;
}

void adicionaAresta(short int* matrixAdj[], int vOrig, int vDest){
	//Matriz eh preenchida de modo simetrico
	matrixAdj[vOrig][vDest] = 1;
	matrixAdj[vDest][vOrig] = 1;
}

int visitaDFS(int n, int v, short int* matrixAdj[], short int* visitado){
	int i=0, qtdMovimentos=0;
	//Marca o nodo atual como visitado
	visitado[n] = 1;

	//Percorre a linha correspondente ao nodo atual procurando
	//por vertices adjacentes. Ao encontrar um vertice, verifica
	//se ele ja foi visitado, se nao foi entao a funçao eh chamada
	//com esse vertice como nodo atual e sao somados 2 movimentos,
	//um de ida e um de volta.
	for(i=0; i<v; i++){
		if(matrixAdj[n][i] == 1 && visitado[i] == 0){
			qtdMovimentos += 2 + visitaDFS(i, v, matrixAdj, visitado);
		}
	}
	
	return qtdMovimentos;
}

//COMENTAR OS PRINTS!!!