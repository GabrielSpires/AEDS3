#ifndef SEMH

#define SEMH


typedef struct{
        int users;
        struct timeval * wait; 
        sem_t * sem;
        } mysem, *ptrmysem; 

void mysem_init(ptrmysem,sem_t*, int);
int mysem_wait(ptrmysem,int);
int mysem_post(ptrmysem,int);
#endif
