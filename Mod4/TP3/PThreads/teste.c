#include <stdio.h>
#include <pthread.h>

int soma = 0;
pthread_mutex_t mut;

void *penes(void *ponei){
	int *br = (int*)ponei;
	pthread_mutex_lock(&mut);
	// printf("%d\n", *br);
	soma++;
	pthread_mutex_unlock(&mut);
}

int main(int argc, char const *argv[]){
	pthread_t threads[30000];
	pthread_mutex_init(&mut, NULL);
	pthread_mutex_lock(&mut);
	pthread_mutex_unlock(&mut);

	long br = 0, i;

	for(i=0; i<30000; i++, br++){
		pthread_create(&threads[i], NULL, penes, (void*)&br);
	}
	for(i=0; i<30000; i++){
		pthread_join(threads[i], NULL);
	}

	printf("%d\n", soma);
	return 0;
}