#ifndef FUNCOES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
	int valores[400], //Vetor que armazena cada conjunto de números
		qtdV,		  //Variável que indica quantos elementos foram lidos
		tamConj;	  //Tamanho do subconjunto na combinação
}Arg;

int somaAchada; //Variável global usada pra interromper os testes

int cmpInt(const void*, const void*);

void bar(int*, int*, int, int, int, int, int);

void foo(int*, int, int, int);

int achaSomaPD(int valores[], int, int);

#endif