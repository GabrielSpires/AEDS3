#include <stdio.h>

int main(){
	int n = 0, i = 0, cont = 0;
	char linha[1000], letra;
	short int alfabeto[26] = {0};
	
	scanf("%d", &n);
	while(n--){
		scanf("%c", &letra);
		do{
			if(letra != ' ' && letra != ',' && letra != '\n'){
				if(alfabeto[letra%26] == 0){
					cont++;
					alfabeto[letra%26] = 1;
				}
			}
			scanf("%c", &letra);
		}while(letra != '\n');
		

		if(cont == 26) printf("frase completa\n");
		else if(cont >= 13) printf("frase quase completa\n");
		else printf("frase mal elaborada\n");

		// printf("%d\n", cont);
		for(i=0; i<26; i++){
			// printf("%d ", alfabeto[i]);
			alfabeto[i] = 0;
		}
		// printf("\n");
		cont = 0;
	}
	return 0;
}