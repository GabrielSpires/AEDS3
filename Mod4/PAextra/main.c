#include <stdio.h>

int main(int argc, char const *argv[]){
	int n, m;
	int numCasas = 0, i, j, d, aux;
	short int digitos[10] = {0};

	while(scanf("%d %d", &n, &m) != EOF){
		numCasas = 0;
		for(i=n; i<=m; i++){
			aux = i;
			for(d=1; d*10<=i; d*=10);
			for(; d>0; d/=10){
				digitos[aux/d]++;
				aux -= d*(aux/d);
			}
			for(j=0; j<10; j++){
				if(digitos[j] > 1) d = 1;
				digitos[j] = 0;
			}
			if(!d) numCasas++;
		}
		printf("%d\n", numCasas);
	}

	return 0;
}