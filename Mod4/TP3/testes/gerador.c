#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// #define qtdeInstancias 10
// #define qtdeAlimentos 21

int main(int argc, char const *argv[]){
	int i, j;
	int qtdeInstancias = atoi(argv[1]);
	int qtdeAlimentos = atoi(argv[2]);

	int vetorAli[qtdeAlimentos];
	int soma = 0;


	srand( (unsigned)time(NULL) );
	printf("%d\n", qtdeInstancias);
	for(i=0; i<qtdeInstancias; i++){
		for(j=0; j<qtdeAlimentos; j++){
			vetorAli[j] = (rand()%101)+1;
			soma += vetorAli[j];
		}
		soma++;
		printf("%d\n", soma);
		for(j=0; j<qtdeAlimentos; j++){
			if(j<qtdeAlimentos-1){
				printf("%d ", vetorAli[j]);
			}
			else{
				printf("%d\n", vetorAli[j]);
			}
		}
		for(j=0; j<qtdeAlimentos; j++){
			vetorAli[j] = 0;
			soma = 0;
		}
	}
	return 0;
}