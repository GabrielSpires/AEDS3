#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#define NUM_OP 900000000
#define X 0.45637


typedef struct tinfo{
	int inicio, fim;
	double soma_parcial;
} tinfo;

void* costlyOP(void *param)
{
	int i;
	double* soma_parcial;
	
	tinfo *t_info = (tinfo *)param;
	soma_parcial = &t_info->soma_parcial;
	(*soma_parcial) = 0.0;
	
	/* realiza operacoes NUM_OP vezes */
	for (i=t_info->inicio; i<t_info->fim; i++) {
		(*soma_parcial) += (cos ( sin(X) ) ) / tan(1-X);
		//(*soma_parcial) += 1.0;
	}

	return NULL;

}

int main(int argc, char** argv)
{
    int n = atoi (argv[1]);
    double soma_total;
	int i;
	int metade, slice;

	struct timeval start, end;
	int tmili;
    
    tinfo x[n];
    pthread_t threads[n];

    printf ("iniciando processamento ... \n");

	gettimeofday(&start, NULL);

    slice = (NUM_OP / n);
	
	/* divide o trabalho para o numero de threads passado
	 com parametro */
    for (i = 0; i < n-1; i++) {
       x[i].inicio = i*slice;
       x[i].fim = (i+1)*slice;
       pthread_create (&threads[i], NULL, costlyOP, &x[i]);
    }
    x[i].inicio = i*slice;
    x[i].fim = NUM_OP;
    pthread_create (&threads[i], NULL, costlyOP, &x[i]);
	
	soma_total = 0.0;	
    for (i = 0; i < n; i++) {
       pthread_join (threads[i], NULL);
       soma_total += x[i].soma_parcial;
    }
	
	gettimeofday(&end, NULL);
	tmili = (int) (1000 * (end.tv_sec - start.tv_sec) +
			(end.tv_usec - start.tv_usec) / 1000);
	printf("tempo decorrido: %d ms\n", tmili);


 //   printf ("Soma total %f\n", soma_total);
	
	return 0;

}
