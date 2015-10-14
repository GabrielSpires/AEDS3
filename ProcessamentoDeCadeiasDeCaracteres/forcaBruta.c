#include <stdio.h>
#include <string.h>

void ForcaBruta(char T[], int n, char P[], int m){
	int i, j, k;
	for(i=0; i<(n-m+1); i++){ //n-m+1 pra nao dar segFault no fim da string
		k = i; //posiçao no texto
		j = 0; //posiçao no padrao
		while(T[k] == P[j] && j < m){
			//percorre o texto e o padrao ao mesmo tempo enquanto os caracteres forem iguais
			j++;
			k++;
		}
		if(j == m){ //Se j == m eh pq existe o padrao no texto
			printf("Casamento na posicao %3d\n", i);
		}
	}
}

int main(int argc, char const *argv[]){
	char texto[] = "brb brazil zil zil broinha";
	char padrao[] = "br";

	ForcaBruta(texto, strlen(texto), padrao, strlen(padrao));

	return 0;
}