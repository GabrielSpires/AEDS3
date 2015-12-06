#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define VECTOR_SIZE 20000000

int ig;
int vetor[VECTOR_SIZE];


int main()
{
	srand (time(NULL));

	for (ig=0; ig < VECTOR_SIZE; ig++) {
		vetor[ig] = rand() % 100;
	}

	int i;
	long int soma_parcial, p1;
	int metade;

	struct timeval start, end;    
	int tmili;                    
	                              
	gettimeofday(&start, NULL);   

	metade = (VECTOR_SIZE/2);

	soma_parcial = 0;
	for (i=0; i<metade; i++) {
		soma_parcial += vetor[i];
	}
	printf("Primeira soma parcial: %ld\n", soma_parcial);
	p1 = soma_parcial;
	soma_parcial = 0;
	for (i=metade; i<VECTOR_SIZE; i++) {
		soma_parcial += vetor[i];
	}
	printf("Segunda soma parcial: %ld\n", soma_parcial);
	printf("Total seq: %ld\n", soma_parcial+p1);

	gettimeofday(&end, NULL);                           
	tmili = (int) (1000 * (end.tv_sec - start.tv_sec) + 
			        (end.tv_usec - start.tv_usec) / 1000);      
	printf("tempo decorrido: %d\n", tmili);             

	
	
	return 0;

}
