#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>

#define MAX_INC 1500000000


int main()
{
	struct timeval inicio, final;
	int tmili;

	//gettimeofday(&inicio, NULL);
	
	unsigned int x = 0, y = 0;
	unsigned int i;
	
	/* imprime os valores iniciais de x e y */
	printf("x: %u, y: %u\n", x, y);
	
	/* incrementa y na primeira thread */
	for (i=0; i<MAX_INC; i++) {
		y = y+1;
	}
	printf("y acabou de ser incrementado\n");
	
	/* incrementa x na primeira thread */
	for (i=0; i<MAX_INC; i++) {
		x = x+1;
	}
	printf("x acabou se ser incrementado\n");

	
	/* mostra os valores de x e y - o valor de x e igual o
		de y porque x foi incrementado na segunda thread */
	printf("x: %u, y: %u\n", x, y);

	//gettimeofday(&final, NULL);
	//tmili = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000);

	//printf("tempo decorrido: %d\n", tmili);
	
	return 0;

}
