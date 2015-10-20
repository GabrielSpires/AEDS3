#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void calcTrab(int *h, int n){
	int i, j;
	long long trab = 0;
	for(i=0; i<n; i++){
		trab += abs(h[i]);
		h[i+1] += h[i];
	}
	printf("%lld\n", trab);
}

int main(int argc, char const *argv[]){
	int i, n, *a;
	scanf("%d", &n);
	do{
		a = (int*)malloc(n * sizeof(int));
		for(i=0; i<n; i++) scanf("%d", &a[i]);
		calcTrab(a, n);
		free(a);
		scanf("%d", &n);
	}while(n != 0);

	return 0;
}