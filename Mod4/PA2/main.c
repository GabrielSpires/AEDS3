#include <stdio.h>
#include <stdlib.h>

typedef struct{
	char letra;
}Codif;

void desloca(Codif *alfabeto, int pos){
	Codif aux = alfabeto[pos];
	int i;
	for(i=pos; i>1; i--){
		alfabeto[i] = alfabeto[i-1];
	}
	alfabeto[i] = aux;
}

int main(int argc, char const *argv[]){
	int i, m, inst = 1, *valores;
	Codif alfabeto[27];

	while(scanf("%d", &m), m != 0){
		printf("Instancia %d\n", inst);
		for(i=1; i<27; i++){
			alfabeto[i].letra = 65+(i-1);
		}
		valores = (int*)malloc(m * sizeof(int));
		for(i=0; i<m; i++){
			scanf("%d", &valores[i]);
		}

		for(i=0; i<m; i++){
			printf("%c", alfabeto[valores[i]].letra);
			desloca(&alfabeto[0], valores[i]);
		}printf("\n\n");
		free(valores);
		inst++;
	}
	return 0;
}