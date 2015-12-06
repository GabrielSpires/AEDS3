#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define VECTOR_SIZE 20000000

int ig;
int vetor[VECTOR_SIZE];


typedef struct tinfo{
	int inicio, fim;
	long int soma_parcial;
} tinfo;

/* soma um pedaco do vetor, dependendo dos indices de
   inicio e fim passados como parametro */
void* sum(void* thread_info)
{
	int i;
	long int* soma_parcial;
	tinfo* t_info = (tinfo *)thread_info;
	soma_parcial = &t_info->soma_parcial;
	(*soma_parcial) = 0;
	
	printf("x: %d %d\n", t_info->inicio, t_info->fim);

	/*soma parte do vetor*/
	for (i=t_info->inicio; i<t_info->fim; i++) {
		(*soma_parcial) += vetor[i];
	}

	printf("Soma parcial: %ld\n", t_info->soma_parcial);
	
	pthread_exit(NULL);

}

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
	
	/* define os pedacos do vetor que cada uma das threads
	   vai ter que somar */
	metade = (VECTOR_SIZE/2);

	tinfo x1;
	x1.inicio = 0;
	x1.fim = metade;
	tinfo x2;
	x2.inicio = metade;
	x2.fim = VECTOR_SIZE;
	
	pthread_t thread1;
	pthread_t thread2;
	
	pthread_create(&thread1, NULL, sum, &x1);
	pthread_create(&thread2, NULL, sum, &x2);
	
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
	printf("Total paralelo: %ld\n", x1.soma_parcial+
			x2.soma_parcial);

	gettimeofday(&end, NULL);
	tmili = (int) (1000 * (end.tv_sec - start.tv_sec) +
			(end.tv_usec - start.tv_usec) / 1000);
	printf("tempo decorrido: %d\n", tmili);


	
	return 0;

}
