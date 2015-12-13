#include <stdio.h>
#include <pthread.h>

int soma = 0;
pthread_mutex_t mut;

void *penes(void *ponei){
	pthread_mutex_lock(&mut);
	soma++;
	pthread_mutex_unlock(&mut);
}

int main(int argc, char const *argv[]){
	pthread_t threads[40];

	long br = 0, i;

	for(i=0; i<40; i++){
		pthread_create(&threads[i], NULL, penes, (void*)&br);
	}
	for(i=0; i<40; i++){
		pthread_join(threads[i], NULL);
	}

	printf("%d\n", soma);
	return 0;
}