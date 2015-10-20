#include <stdio.h>
#include <stdlib.h>
 
typedef struct{
    int x, y, z, esc;
}Aresta;

void merge(Aresta arr[], int l, int m, int r){
    int i, j, k; 
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    Aresta L[n1], R[n2];
 
    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1+ j];
 
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2){
        if (L[i].z <= R[j].z){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(Aresta arr[], int l, int r){
   if (l < r){
      int m = l+(r-l)/2;
      mergeSort(arr, l, m);
      mergeSort(arr, m+1, r);
      merge(arr, l, m, r);
   }
}

void criaMST(Aresta* estrada, int* conectado, int m, int n){
    int i = 0, j = 0;
    int custoTotal = 0, custoMst = 0;
    for (i = 0; i < n; i++){
        custoTotal += estrada[i].z;
        int aux = 0;
        
        if (conectado[estrada[i].x] != conectado[estrada[i].y]){
            aux = conectado[estrada[i].y];
            for (j = 0; j < m; j++){ //problema aqui
                if (conectado[j] == aux){
                    conectado[j] = conectado[estrada[i].x];
                }
            }
            custoMst += estrada[i].z;
            /*
            for (k = 0; k < m; k++){
                printf("%d ", conectado[k]);
            }printf("\n");
            */
        }

    }

    printf("%d\n", custoTotal - custoMst);
}
 
int main(int argc, char const *argv[]){
    int i = 0;
    int m = 0; //junçoes (vertices)
    int n = 0; //estradas (arestas)
    Aresta* estrada;
    int* conectado;
 
    do{
        scanf("%d %d", &m, &n);
        conectado = (int*)calloc(m,sizeof(int));
        estrada = (Aresta*)malloc(n*sizeof(Aresta));
 
        for (i = 0; i < m; i++){
            conectado[i] = i;
        }
        i=n;
        while(i--){
            scanf("%d %d %d", &estrada[i].x, &estrada[i].y, &estrada[i].z);
            estrada[i].esc = 0;
        }
        mergeSort(estrada, 0, n);
        /*
        for (i = 0; i < n; ++i){
            printf("%d\n", estrada[i].z);
        }
        */
        if(m && n) criaMST(estrada, conectado, m, n);
    }while (m && n);
 
    return 0;
}