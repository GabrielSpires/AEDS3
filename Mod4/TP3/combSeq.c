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
	int i;
	int p[100000];
	for(i=0; i<100000; i++) p[i] = i;
	int n = 100000;
	for(i=0; i<n; i++){
		// p é o vetor
		// n é o tamanho do vetor
		// k é o tamanho do sub-conjunto da combinação (quantos elementos escolher)
		foo(p, n, i);
	}
	return 0;
}