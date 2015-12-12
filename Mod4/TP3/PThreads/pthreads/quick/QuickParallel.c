#define STACK_SIZE 10000 
#define KEEPONE
#define LIMITE_PARTICAO 375

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <thread.h>
#include <semaphore.h>
#include <sys/resource.h>
#include <time.h>
#include "myprof.h"
#include "barrier.h"
#include "newsem.h"

typedef sem_t VetorSemaforos[2];
typedef int Indice;
typedef int Flags;

typedef struct Item_Def{
  Indice low, high;
}Item, *ItemPtr;

typedef Item Pilha[STACK_SIZE];

ItemPtr topo;
Flags procbusy, pilhavazia;

int NUM_THREADS=4;
thread_t *tid;
sem_t mutex;
mysem mymutex;

void *Ordena(void *);  /* Codigo dos processos */

int *Numeros, n=100000;
int *Particoes;
Pilha Stack;
barr_t bar;
int NParticoes, Max;

myprof_t *profParticao, *profInsercao, *profExec, *profLoop;



void vet_init(void)
{
  int i;

  srand(time((time_t*)0));
  for(i=0; i<n; i++)
    Numeros[i] = rand() % (n * 5);
  for(i=0; i<NUM_THREADS; i++)
    Particoes[i] = 0;
  NParticoes = 1;
  Max = 1;
  topo = &(Stack[0]);
  topo->low = 0;
  topo->high = (n-1);
  pilhavazia = 0;
  procbusy = 0;
}

void print(void)
{
  int i; 

  for(i=0; i<n; i++){
    printf("%6d", Numeros[i]);
    if((i+1)%12 == 0)
      printf("\n");
  }
  printf("\n");
}

void Insercao(int *A, Indice Esq, Indice Dir){
	int tmp, i, j;

	for(j=Esq+1; j<=Dir; j++){
		i = j - 1;
		tmp = A[j];
		while((i >= 0) && (tmp < A[i])){
			A[i+1] = A[i];
			i--;
		}
		A[i+1] = tmp;
	}
}

void Particao(int *A, Indice Esq, Indice Dir, Indice *i, Indice *j)
{
  int x, w;

  *i = Esq;
  *j = Dir;
  x = A[(*i + *j) / 2];   /* obtem o pivo x */
  do {
    while (A[*i] < x)
      (*i)++;
    while (A[*j] > x)
      (*j)--;
    if (*i <= *j) {
      w = A[*i];
      A[*i] = A[*j];
      A[*j] = w;
      (*i)++;
      (*j)--;
    }
  } while (*i <= *j);   /* Particao */
}


/*
==========================================================================
*/

void *Ordena(void *arg)
{
  Indice i, j, l, r;
  ItemPtr myitemptr;
  Item myitem;
  int z, myself;

  for(z=0; z<NUM_THREADS; z++)
	if(pthread_equal(pthread_self(), tid[z]))
		myself = z;

  myitemptr = NULL;
  mybarrier(&bar, myself);
#ifdef DEBUG
  fprintf(stderr, "%d comeca a executar...\n", myself);
#endif
  myprof_init(&(profExec[myself]));
  myprof_init(&(profParticao[myself]));
  myprof_init(&(profInsercao[myself]));
  myprof_init(&(profLoop[myself]));
  myprof_start(&(profExec[myself]));
  while(procbusy || !pilhavazia){

    if(!myitemptr){
      if(!pilhavazia){
         mysem_wait(&mymutex, myself);
         if (!pilhavazia){
           myitem.low = topo->low;
           myitem.high = topo->high;
	   myitemptr = &myitem;
	   if(topo == &(Stack[0])){
	     topo = NULL;
	   }else{
	     topo--;
	   }
           NParticoes--;
 
           procbusy |= (1 << myself);
           if(topo) pilhavazia = 0;
           else pilhavazia = 1;
         }
         mysem_post(&mymutex, myself);
      }
      else{
         if (procbusy & (1 << myself)){
           mysem_wait(&mymutex, myself);
           myitemptr = NULL;
           procbusy = ~procbusy;
           procbusy |= (1 << myself);
           procbusy = ~procbusy;
           mysem_post(&mymutex, myself);
         }
         if (pilhavazia){
           myprof_start(&(profLoop[myself]));
           while (procbusy && pilhavazia);
           myprof_end(&(profLoop[myself]));
         }
      }
    }
    if(myitemptr){  /* Entra se houver particao para ordenar */

      if((myitem.high - myitem.low + 1) > LIMITE_PARTICAO){
        myprof_start(&(profParticao[myself]));
        Particao(Numeros, myitem.low, myitem.high, &i, &j);
        myprof_end(&(profParticao[myself]));
        Particoes[myself]++;

        l = myitem.low;
        r = myitem.high;
      }else{
	myprof_start(&(profInsercao[myself]));
        Insercao(Numeros, myitem.low, myitem.high);
	myprof_end(&(profInsercao[myself]));
        j = i = 1;
        l = 2;
        r = 0;
      }

      if((l < j) || (i < r)){
	int JaPegou;

#ifdef KEEPONE
        JaPegou = 0;
#else
	JaPegou = 1;
#endif
        if (l < j){
#ifdef KEEPONE
          myitem.low = l;
          myitem.high = j;
	  JaPegou = 1;
#endif
#ifndef KEEPONE
	  mysem_wait(&mymutex, myself);
	  if(topo){
		topo++;
	  }else{
		topo = &(Stack[0]);
	  }
	  topo->low = l;
	  topo->high = j;
	  NParticoes++;
	  if(NParticoes > Max)
		Max = NParticoes;
	  mysem_post(&mymutex, myself);
#endif 
        }
        if (i < r){
	  if(JaPegou){
	    mysem_wait(&mymutex, myself);
	    if(topo){
		topo++;
	    }else{
		topo = &(Stack[0]);
	    }
            topo->low = i;
            topo->high = r;
            NParticoes++;
            if(NParticoes > Max)
 		Max = NParticoes;
	    mysem_post(&mymutex, myself);
      	  }
	  else{
	    myitem.low = i;
	    myitem.high = r;
 	  }
        }
#ifdef KEEPONE
	myitemptr = &myitem;
	mysem_wait(&mymutex, myself);
 	if(topo) pilhavazia = 0;
	else pilhavazia = 1;
	mysem_post(&mymutex, myself);
#endif
#ifndef KEEPONE
	myitemptr = NULL;
	mysem_wait(&mymutex, myself);
	pilhavazia = 0;
	mysem_post(&mymutex, myself);
#endif
      }
      else{
        myitemptr = NULL;
      }
    }
  }
  myprof_end(&(profExec[myself]));
  return (void*)0; 
}  /* Ordena */


void usage()
{
  fprintf(stderr,"QuickParallel - threaded parallel quicksort\n");
  fprintf(stderr,"-h                       (prints this message)\n");
  fprintf(stderr,"-n  num                  (vector size)\n");
  fprintf(stderr,"-t  num                  (threads)\n");
}

void parse_args(int argc, char ** argv)
{
   extern char *optarg;
   int c;
   while ((c=getopt(argc,argv,"n:t:h")) != EOF)
     switch(c){
       case 'n':
               n = atoi(optarg);
               break;
       case 't':
               NUM_THREADS = atoi(optarg);
               break;
       case 'h':
       default:
                usage();
                exit(1);
     }
}


/*
==========================================================================
*/

int main(int argc, char *argv[])
{
   int i, j;

   parse_args(argc,argv);
   Numeros = (int *)malloc(n * sizeof(int));
   profLoop = (ptr_myprof_t)malloc(NUM_THREADS * sizeof(myprof_t));
   profParticao = (ptr_myprof_t)malloc(NUM_THREADS * sizeof(myprof_t));
   profInsercao = (ptr_myprof_t)malloc(NUM_THREADS * sizeof(myprof_t));
   profExec = (ptr_myprof_t)malloc(NUM_THREADS * sizeof(myprof_t));
   tid = (thread_t *)malloc(NUM_THREADS * sizeof(thread_t));
   Particoes = (int *)malloc(NUM_THREADS * sizeof(int));
   sem_init(&mutex, 1, 1);
   mysem_init(&mymutex, &mutex, NUM_THREADS);
   vet_init();
   init_mybarrier(&bar, NUM_THREADS);

   for(i=0; i<NUM_THREADS; i++)
      pthread_create(&(tid[i]), NULL, Ordena, 0);

   for(i=0; i<NUM_THREADS; i++)
      pthread_join(tid[i], NULL); 

   printf("%d processo(s) foi(ram) usado(s)\n", NUM_THREADS);
   printf("Tamanho maximo da pilha: %d\n\n", Max);
   for (i=0; i<NUM_THREADS; i++){
     printf("%2d proc  %6d particoes\n", i, Particoes[i]);
     printf("%2d Execucao %5ld.%.6ld usr: %5ld.%.9ld sys: %5ld.%.9ld\n",
       i,profExec[i].elapsed.tv_sec, profExec[i].elapsed.tv_usec,
       profExec[i].u_sec, profExec[i].u_nsec,
       profExec[i].s_sec, profExec[i].s_nsec);
     printf("%2d Insercao %5ld.%.6ld usr: %5ld.%.9ld sys: %5ld.%.9ld\n",
       i,profInsercao[i].elapsed.tv_sec, profInsercao[i].elapsed.tv_usec,
       profInsercao[i].u_sec, profInsercao[i].u_nsec,
       profInsercao[i].s_sec, profInsercao[i].s_nsec);
     printf("%2d Particao %5ld.%.6ld usr: %5ld.%.9ld sys: %5ld.%.9ld\n",
       i,profParticao[i].elapsed.tv_sec, profParticao[i].elapsed.tv_usec,
       profParticao[i].u_sec, profParticao[i].u_nsec,
       profParticao[i].s_sec, profParticao[i].s_nsec);
     printf("%2d Pilha    %5ld.%.6ld usr: %5ld.%.9ld sys: %5ld.%.9ld\n",
       i,profLoop[i].elapsed.tv_sec, profLoop[i].elapsed.tv_usec,
       profLoop[i].u_sec, profLoop[i].u_nsec,
       profLoop[i].s_sec, profLoop[i].s_nsec);
     printf("%2d Barreira %5ld.%.6ld\n",
       i,bar.wait[i].tv_sec, bar.wait[i].tv_usec);
     printf("%2d Mutex    %5ld.%.6ld\n",
       i,mymutex.wait[i].tv_sec, mymutex.wait[i].tv_usec);
   }
   for(j=1; j<n; j++)
      if(Numeros[j] < Numeros[j-1]){
		printf("O vetor nao esta ordenado...\n");
		break;
      }
   return 0;
}
