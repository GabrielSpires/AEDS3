#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>

#define MAX_INC 1500000000

/* essa funcao sera executada pela segunda thread enquanto
   a thread principal incrementa o valor de y */
void *inc_x(void *x_void_ptr)
{

	/* incrementa x */
	unsigned int i;
	unsigned int* x_ptr = (unsigned int*)x_void_ptr;

	for (i=0; i<MAX_INC; i++) {
		(*x_ptr) = (*x_ptr) + 1;
	}
	
	printf("x acabou de ser incrementado\n");
    
	return NULL;

}

int main()
{
	struct timeval inicio, final;
	int tmili;

	//gettimeofday(&inicio, NULL);

	unsigned int x = 0, y = 0;
	unsigned int i;
	
	/* imprime os valores iniciais de x e y */
	printf("x: %u, y: %u\n", x, y);
	
	/* essa variavel e a referencia para a segunda thread */
	pthread_t inc_x_thread;
	pthread_t inc_y_thread;
	
	/* cria a segunda thread que vai executar a funcao inc_x */
	if(pthread_create(&inc_x_thread, NULL, inc_x, &x)) {
	
		fprintf(stderr, "Error creating thread\n");
		return 1;

	}
	/* cria a terceira thread que vai executar a funcao inc_x
	para o y */
	if(pthread_create(&inc_y_thread, NULL, inc_x, &y)) {
	
		fprintf(stderr, "Error creating thread\n");
		return 1;

	}
	
	/* a thread principal espera a segunda thread acabar para
		continuar a execução */
	if(pthread_join(inc_x_thread, NULL)) {
	
		fprintf(stderr, "Error joining thread\n");
		return 2;
	
	}

	/* a thread principal espera a terceira thread acabar para
		continuar a execução */
	if(pthread_join(inc_y_thread, &s)) {
	
		fprintf(stderr, "Error joining thread\n");
		return 2;
	
	}

	/* mostra os valores de x e y - o valor de x e igual o
		de y porque x foi incrementado na segunda thread */
	printf("x: %u, y: %u\n", x, y);

	//gettimeofday(&final, NULL);
	//tmili = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000);
	//printf("tempo decorrido: %d\n", tmili);
	
	return 0;

}
