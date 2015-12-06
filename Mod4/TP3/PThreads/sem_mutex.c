#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define VECTOR_SIZE 200000

int ig;
int vetor[VECTOR_SIZE];
long int soma_total;


typedef struct tinfo{
	int inicio, fim;
	long int soma_parcial;
} tinfo;

pthread_mutex_t mutexsum;

/* realiza a soma do vetor */
void *sum_vetor(void *param)
{
	int i;
	/* increment x to 100 */
	tinfo *t_info = (tinfo *)param;
	
	/*soma parte do vetor - como o mutex nao esta sendo usado,
	 as duas variaveis vao tentar escrever na mesma variavel ao
	 mesmo tempo, gerando um resultado diferente do esperado*/
	//pthread_mutex_lock (&mutexsum);
	for (i=t_info->inicio; i<t_info->fim; i++) {
		soma_total += vetor[i];
	}
	//pthread_mutex_unlock (&mutexsum);

	return NULL;

}

int main()
{
	srand (time(NULL));

	for (ig=0; ig < VECTOR_SIZE; ig++) {
		vetor[ig] = rand() % 100;
	}

	int i;
	long int p1, soma;
	int metade;

	struct timeval start, end;
	int tmili;

	//gettimeofday(&start, NULL);

	metade = (VECTOR_SIZE/2);

	tinfo x1;
	x1.inicio = 0;
	x1.fim = VECTOR_SIZE;
	tinfo x2;
	x2.inicio = 0;
	x2.fim = VECTOR_SIZE;
	
	//pthread_mutex_init(&mutexsum, NULL);

	pthread_t thread1;
	pthread_t thread2;
	
	pthread_create(&thread1, NULL, sum_vetor, &x1);
	pthread_create(&thread2, NULL, sum_vetor, &x2);
	
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
	printf("Total paralelo: %ld\n", soma_total);

	//gettimeofday(&end, NULL);
	//tmili = (int) (1000 * (end.tv_sec - start.tv_sec) +
	//		(end.tv_usec - start.tv_usec) / 1000);
	//printf("tempo decorrido: %d\n", tmili);

	soma = 0;
	for (ig=0; ig < VECTOR_SIZE; ig++) {
		soma += vetor[ig];
	}
	printf("Total sequencial: %ld\n", soma*2);


	
	return 0;

}











