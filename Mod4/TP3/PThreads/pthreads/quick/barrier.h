#ifndef __BARRIER__
#define __BARRIER__

#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <malloc.h>

typedef struct barr{
        int users;
        int counter;
        int in_barrier;
        struct timeval * wait;
        sem_t in_mutex;
        sem_t out_mutex;
        sem_t barrier;
        } barr_t, *ptr_barr_t;
barr_t barr;

extern void init_mybarrier(ptr_barr_t, int);
extern void mybarrier(ptr_barr_t, int);

#endif
