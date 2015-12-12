#include "barrier.h"

void init_mybarrier(b, num)
  ptr_barr_t b;
  int      num; 
{
  int i;
  b->users = num;
  b->counter = 0;
  b->in_barrier = 0;
  sem_init(&(b->in_mutex),1,1);
  sem_init(&(b->out_mutex),1,0);
  sem_init(&(b->barrier),1,0);
  b->wait = (struct timeval *) malloc(sizeof(struct timeval)*b->users);
  for (i=0; i<b->users; i++)
    b->wait[i].tv_sec = b->wait[i].tv_usec = 0;
}

void mybarrier (b,myself)
  ptr_barr_t b;
  int myself;
{
  int i;
  struct timeval entered, exited;
  
  gettimeofday(&entered, (void *)0); 
  sem_wait(&(b->in_mutex));
  if (b->counter == b->users -1)
  {
    b->counter = 0;
    for (i=0; i<b->users-1; i++)
      sem_post(&(b->barrier));
    for (i=0; i<b->users-1; i++)
      sem_wait(&(b->out_mutex));
    b->in_barrier = 0;
    sem_post(&(b->in_mutex));
  }
  else
  {
    b->counter++;
    b->in_barrier |= (1<<myself);
    sem_post(&(b->in_mutex));
    sem_wait(&(b->barrier));
    sem_post(&(b->out_mutex));
  }
  gettimeofday(&exited, (void *)0); 
  b->wait[myself].tv_sec = exited.tv_sec - entered.tv_sec; 
  b->wait[myself].tv_usec = exited.tv_usec - entered.tv_usec; 
  if (b->wait[myself].tv_usec < 0){
    b->wait[myself].tv_sec --;
    b->wait[myself].tv_usec += 1000000;
  }
}
