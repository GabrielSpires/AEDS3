#include "lista.h"

int main(int argc, char const *argv[]){
	int i = 0, n = 0; //Numero de palavras abreviadas
	char palavra[31], separador;
	lista palavras[27];

	do{
		for(i=0; i<27; i++) criaLista(&palavras[i]);
		
		do{
			scanf("%s%c", palavra, &separador);
			if(palavra[0] == '.') break;
			inserir(palavra, &palavras[palavra[0]%97]);
			copiaPalavra(palavra, &palavras[palavra[0]%97], &palavras[26]);
			// printf("%s ", palavra);
		}while(separador == ' ');
		// printf("\n");
		if(palavra[0] == '.') break;

		iterador j, k;
		int maiorEconomia = 0;
		for(i=0; i<26; i++){
			for(j = inicio(&palavras[i]); j != final(&palavras[i]); j=next(j)){
				if(j->economia > maiorEconomia){
					maiorEconomia = j->economia;
					k = j;
				}
			}
			for(j = inicio(&palavras[i]); j != final(&palavras[i]); j=next(j)){
				if(j->economia == maiorEconomia){
					if(strlen(j->key) > 2){
						j->keyAbreviada[1] = '.';
						j->keyAbreviada[2] = '\0';
						j->abreviar = 1;
						n++;
						break;
					}
				}
			}
			// printf("%d: %d\n", i, maiorEconomia);

			maiorEconomia = 0;
		}

		for(j = inicio(&palavras[26]); j != final(&palavras[26]); j=next(j)){
			printf("%s", j->keyAbreviada);
			if(next(j) != final(&palavras[26])) printf(" ");
		}
		if(inicio(&palavras[26]) != final(&palavras[26])){
			printf("\n");
		}

		printf("%d\n", n);
		for(i=0; i<26; i++){
			for(j = inicio(&palavras[i]); j != final(&palavras[i]); j=next(j)){
				if(j->abreviar == 1)
					printf("%s = %s\n", j->keyAbreviada, j->key);
			}
		}

		n = 0;
		for(i=0; i<27; i++) liberaLista(&palavras[i]);
	}while(1);

	return 0;
}