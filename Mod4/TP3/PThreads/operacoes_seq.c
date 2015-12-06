#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#define NUM_OP 900000000
#define X 0.45637


int main()
{
	int i;
	double soma_total;

	struct timeval start, end;    
	int tmili;                    
    printf ("iniciando processamento ... \n");
	
	gettimeofday(&start, NULL);   

	soma_total = 0.0;
	for (i=0; i<NUM_OP; i++) {
		soma_total += (cos ( sin(X) ) ) / tan(1-X);
	}

	gettimeofday(&end, NULL);                           
	tmili = (int) (1000 * (end.tv_sec - start.tv_sec) + 
			        (end.tv_usec - start.tv_usec) / 1000);      
    printf ("Soma total %f\n", soma_total);
	printf("tempo decorrido: %d\n ms", tmili);             

	
	
	return 0;

}
