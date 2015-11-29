#include <stdio.h>

int main(int argc, char const *argv[]){
	int t, soma, valores[300], qtdV, i;
	char proxChar;

	scanf("%d", &t);

	while(qtdV = 0, t--){
		scanf("%d", &soma);

		do{
			scanf("%d%c", &valores[qtdV], &proxChar);
			qtdV++;
		}while(proxChar != '\n');

		printf("%d\n", soma);
		for(i=0; i<qtdV; i++){
			printf("%d ", valores[i]);
		}printf("\n");
		
	}
	return 0;
}