#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <thread.h>
#include <semaphore.h>

int NUM_THREADS=4;
thread_t *tid;
sem_t mutex;
int Numeros[10],n=10, soma=0;

void *Soma(void *);  /* Codigo dos processos */
void vet_init(void) {
  int i;
  srand(time((time_t*)0));
  printf("Vetor:");
  for(i=0; i<n; i++){
    Numeros[i] = rand() % (n * 5);
    printf("%d ",Numeros[i]);
  }
  printf("\n");
}

void *Soma(void *arg) {
  int z, myself,res=0;

  for(z=0; z<NUM_THREADS; z++)
    if(pthread_equal(pthread_self(), tid[z])) myself = z;
  for (z=myself; z<n; z+=NUM_THREADS) res += Numeros[z];
  sem_wait(&mutex);
  soma += res;
  printf("Proc %d somou %d ==> %d\n", myself,res,soma);
  sem_post(&mutex);
  return (void*)0; 
} 

int main(int argc, char *argv[])
{
   int i;

   tid = (thread_t *)malloc(NUM_THREADS * sizeof(thread_t));
   sem_init(&mutex, 1, 1);
   vet_init();
   for(i=0; i<NUM_THREADS; i++) pthread_create(&(tid[i]), NULL, Soma, 0);
   for(i=0; i<NUM_THREADS; i++) pthread_join(tid[i], NULL); 
   printf("A soma e' %d\n",soma);
   return 0;
}
