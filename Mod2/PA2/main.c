#include <stdio.h>
#include <string.h>

void cripto(char* linha, int tam){
	int i, tamAux = tam;
	char aux;
	for (i=0; i<tam; i++){
		if((linha[i] >= 97 && linha[i] <= 122) ||
		   (linha[i] >= 65 && linha[i] <= 90)){
		   	linha[i] += 3;
		}
	}
	for (i=0; i<tamAux-1; i++){
		tamAux--;
		aux = linha[i];
		linha[i] = linha[tamAux-1];
		linha[tamAux-1] = aux;
	}
	for (i=(tam-1)/2; i<tam-1; i++){
		linha[i] -= 1;
	}
}

int main(){
	int n = 0;
	char linha[1000], c;
	scanf("%d", &n);
	scanf("%c", &linha[0]);; //pega o \n
	while(n--){
		fgets(linha, 1000, stdin);
		cripto(&linha[0], strlen(linha));
		printf("%s", linha);
	}
	return 0;
}