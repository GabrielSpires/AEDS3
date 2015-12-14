#ifndef FUNCOES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
	int valores[310], //Vetor que armazena cada conjunto de números
		qtdV,		   //Variável que indica quantos elementos foram lidos
		tamConjInicial,//Tamanho do subconjunto na combinação
		tamConjFinal,  //Tamanho do subconjunto na combinação
		soma; 		   //Valor da soma
}Arg;

int somaAchada; //Variável global usada pra interromper os testes
pthread_mutex_t mut;

int cmpInt(const void*, const void*);

void bar(int*, int*, int, int, int, int, int);

void *foo(void *);

int achaSomaPD(int valores[], int, int);

#endif