#include <stdlib.h>
#include <sys/time.h>
#include "semaphore.h"
#include "newsem.h"

void mysem_init(ptrmysem s,sem_t*sem, int users){
  int i;
  s->users = users;
  s->sem = sem;
  s->wait = (struct timeval*) malloc(s->users*sizeof(struct timeval));
  for (i=0; i<s->users; i++)
    s->wait[i].tv_sec = s->wait[i].tv_usec = 0;
}

int mysem_wait(ptrmysem s,int myself){
  int ret;
  struct timeval entered, exited; 
//  ret = sem_trywait(s->sem);
  ret = -1;
  if (ret == -1){
    gettimeofday(&entered, (void *) 0);
    ret = sem_wait(s->sem);
    gettimeofday(&exited, (void *) 0);
    if((exited.tv_usec - entered.tv_usec) < 0){
 	  exited.tv_sec--;
	  exited.tv_usec += 1000000;
    }
    s->wait[myself].tv_sec += exited.tv_sec - entered.tv_sec;
    s->wait[myself].tv_usec += exited.tv_usec - entered.tv_usec;
    s->wait[myself].tv_sec += s->wait[myself].tv_usec / 1000000;
    s->wait[myself].tv_usec %= 1000000;
  }
  return ret;
}


int mysem_post(ptrmysem s,int myself){
  return sem_post(s->sem);
}
