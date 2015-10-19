#include <stdio.h>
#include <stdlib.h>
 
typedef struct{
    int x, y, z;
}Aresta;

//Funçao que procura o numero do componente pertencente ao vertice original do componente
//Essa funçao eh usada pra evitar que ao se procurar os vertices pertencentes a um
//componente, o vetor inteiro seja percorrido fazendo com que o algoritmo rode em
//complexidade O(M*N)

int procuraComponente(int* conectado, int x){
    int i = 0;
    for (i = x; conectado[i] != i; i = conectado[i]);
    return i;
}

int cmp(const void *a, const void *b){
    return ( (*(Aresta *)a).z - (*(Aresta *)b).z );
} 

void criaMST(Aresta* estrada, int* conectado, int m, int n){
    int i = 0;
    int custoTotal = 0, custoMst = 0;
    for (i = 0; i < n; i++){
        custoTotal += estrada[i].z;
        int achaX = procuraComponente(conectado, estrada[i].x);
        int achaY = procuraComponente(conectado, estrada[i].y);

        if (achaX != achaY){
            conectado[procuraComponente(conectado, estrada[i].x)] = procuraComponente(conectado, estrada[i].y);
            custoMst += estrada[i].z;
        }
    }
    printf("%d\n", custoTotal - custoMst);
}
 
int main(int argc, char const *argv[]){
    int i = 0;
    int m = 0; //junçoes (vertices)
    int n = 0; //estradas (arestas)
    Aresta* estrada; //Vetor de arestas
    int* conectado; //Vetor que guarda os numeros dos componentes conectados
 
    do{
        scanf("%d %d", &m, &n);
        conectado = (int*)calloc(m,sizeof(int));
        estrada = (Aresta*)malloc(n*sizeof(Aresta));
        
        //Preenche o vetor com um numero para cada posiçao
        //levando em consideraçao que cada vertice começa como um
        //componente isolado do grafo
        for (i = 0; i < m; i++){
            conectado[i] = i;
        }

        //Preenche o vetor de estradas com os valores do x, y e das arestas
        i=n;
        while(i--){
            scanf("%d %d %d", &estrada[i].x, &estrada[i].y, &estrada[i].z);
        }
        //Usa quicksort nativo do C para ordenar o vetor de arestas
        //pelo valor do peso das arestas
        qsort(estrada, n, sizeof(Aresta), cmp);

        //Roda a funçao que cria a arvore geradora minima
        if(m && n) criaMST(estrada, conectado, m, n);

    }while (m && n);
 
    return 0;
}