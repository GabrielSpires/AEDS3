#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <thread.h>
#include <semaphore.h>
#include "barrier.h"

#define NUM 100000

int NUM_THREADS=2;
thread_t *tid;
sem_t mutex;
barr_t barr;
char numeros[NUM];
int n=NUM, primo=0;

void* Marca(void *);  /* Codigo dos processos */

void vet_init(void) {
  int i;
  for(i=0; i<n; i++){
    numeros[i] = 0;
  }
}

void *Marca(void *arg) {
  int i,j,z, myself,res=0;
  int lim = ceil(sqrt(NUM*1.0));

  for(z=0; z<NUM_THREADS; z++)
    if(pthread_equal(pthread_self(), tid[z])) myself = z;

  mybarrier(&barr,myself);

  for (i=2; i<=lim; i++){
    sem_wait(&mutex);
    if (!numeros[i]) {
      numeros[i] = -1;
      res = i;
      printf("%d esta marcando %d\n",myself,i);
    }
    sem_post(&mutex);
    if (res == i)
      for (j=i*2; j<NUM; j+= i){
        numeros[j] = 1; 
      }  
  }
  mybarrier(&barr,myself);
  return (void*)0; 
} 

int main(int argc, char *argv[])
{
   int i;

   tid = (thread_t *)malloc(NUM_THREADS * sizeof(thread_t));
   sem_init(&mutex, 1, 1);
   vet_init();
   init_mybarrier(&barr,NUM_THREADS);
   for(i=0; i<NUM_THREADS; i++) pthread_create(&(tid[i]), NULL, Marca, 0);
   for(i=0; i<NUM_THREADS; i++) pthread_join(tid[i], NULL); 
   for (i=1; i<NUM; i++)
     primo += (numeros[i]==-1 || !numeros[i]);
   printf("O numero de primos menores que %d e' %d\n",NUM,primo);
   return 0;
}

