#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <thread.h>
#include <semaphore.h>
#include "barrier.h"

#define NUM 20

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
  int block = rint(1.0*NUM/NUM_THREADS);
  int start,end;

  for(z=0; z<NUM_THREADS; z++)
    if(pthread_equal(pthread_self(), tid[z])) myself = z;

  start = myself*block;
  start = (start<1?1:start);
  end = (myself+1)*block;
  end = (end>NUM?NUM:end); 

  printf("Proc %d verificando de %d a %d\n", myself, start,end-1);

  mybarrier(&barr,myself);

  for (i=2; i<=lim; i++){
    if (!numeros[i]){
      for (z=(i>start?i+1:start); z<end; z++)
        if (z%i==0) break; 
#ifdef DEBUG
      printf("%d Testando %d a partir de %d\n", myself,i,z);
#endif
      for (j=z; j<end; j+= i){
        numeros[j] = 1; 
#ifdef DEBUG
        printf("%d marcando %d\n", myself,j);
#endif
      }  
      mybarrier(&barr,myself);
    }
  }

  for (z=start; z<end; z++) res += !numeros[z];
  sem_wait(&mutex);
  primo += res;
  printf("Proc %d somou %d ==> %d\n", myself,res,primo);
  sem_post(&mutex);
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
   printf("O numero de primos menores que %d e' %d\n",NUM,primo);
   return 0;
}


