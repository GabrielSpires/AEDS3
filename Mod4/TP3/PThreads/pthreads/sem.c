/*
 *	File	: sem.c
 *
 *	Title	: semaphore implementation
 *
 *	Short	: semaphore implementation using condition variables
 *
 *	Long	:
 *
 *	Author	: Wagner Meira Jr.
 *
 *	Date	: 21 January 2000
 *
 *	Revised	:
 */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct{
  pthread_mutex_t * mutex;
  pthread_cond_t * pass;
  int waiting;
  int avail;
} sema_t, *ptr_sema_t;

void sema_init(ptr_sema_t,int);
void sema_post(ptr_sema_t);
void sema_wait(ptr_sema_t);
void sema_destroy(ptr_sema_t);

void sema_init(ptr_sema_t s, int avail){
  
  s->mutex = (pthread_mutex_t *) malloc (sizeof (pthread_mutex_t));
  if (s->mutex == NULL){
    fprintf(stderr,"sema_init: malloc error\n"); 
    exit(2);
  }
  s->pass = (pthread_cond_t *) malloc (sizeof (pthread_cond_t));
  if (s->pass == NULL){ 
    free (s->mutex); 
    fprintf(stderr,"sema_init: malloc error\n"); 
    exit(2);
  }
  pthread_mutex_init (s->mutex, NULL);
  pthread_cond_init (s->pass, NULL);
  s->waiting = 0;
  s->avail = avail; 
} 

void sema_destroy(ptr_sema_t s){
  pthread_mutex_destroy (s->mutex);
  pthread_cond_destroy (s->pass);
}

void sema_wait(ptr_sema_t s){
  pthread_mutex_lock(s->mutex);
  if (!s->avail)
    s->waiting ++;
  while (!s->avail){
    pthread_cond_wait(s->pass, s->mutex);
  }
  s->avail --;
  s->waiting --;
  pthread_mutex_unlock(s->mutex);
}

void sema_post(ptr_sema_t s){
  pthread_mutex_lock(s->mutex);
  s->avail ++;
  pthread_mutex_unlock(s->mutex);
}

int NUM_THREADS=4;
pthread_t *tid;
sema_t mutex;
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
  sema_wait(&mutex);
  soma += res;
  printf("Proc %d somou %d ==> %d\n", myself,res,soma);
  sema_post(&mutex);
  return (void*)0; 
} 

int main(int argc, char *argv[])
{
   int i;

   tid = (pthread_t *)malloc(NUM_THREADS * sizeof(pthread_t));
   sema_init(&mutex, 1);
   vet_init();
   for(i=0; i<NUM_THREADS; i++) pthread_create(&(tid[i]), NULL, Soma, 0);
   for(i=0; i<NUM_THREADS; i++) pthread_join(tid[i], NULL); 
   printf("A soma e' %d\n",soma);
   return 0;
}
