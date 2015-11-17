#include <stdio.h>
#include <stdlib.h>

void fooR(int* src, int* v, int srcIndex, int vIndex, int srcSize, int vSize){
	int i;
	if(vIndex==vSize){
		for(i=0; i<vSize; i++)
			printf("%d ", v[i]);
		printf("\n");
	}
	else{
		for(i=srcIndex; i<srcSize; i++){
			v[vIndex] = src[i];
			fooR(src, v, i+1, vIndex+1, srcSize, vSize);
		}
	}
}

void foo(int* src, int size, int k){
	int *v;
	v = (int*)calloc(k, sizeof(int));
	fooR(src, v, 0, 0, size, k);
}

int main(){
	int t;//numero de casos teste
	int i, j;
	scanf("%d", &t);
	for( i = 0; i < t; i++){
		int n , k;// numero de rotas e numero de planetas a serem reconquistados
		int *p;
		scanf("%d %d", &n, &k);
		p = (int*)malloc(sizeof(int)*n);
		int tamMax = 0;
		int *distPlanetas;
		distPlanetas = (int*)calloc((n+1), sizeof(int));
		int planetas;
		for( j = 0; j < n+1; j++){
			scanf("%d", &planetas);
			tamMax += planetas;
			p[j] = j+1;
			distPlanetas[j] = planetas;
		}
		foo(p, n, k);
	}
	return 0;
}