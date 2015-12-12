#ifndef MYPROF_H
#define MYPROF_H

#include <sys/time.h>
#include <sys/lwp.h>

typedef struct{
    struct timeval elapsed;
    long u_sec, u_nsec, s_sec, s_nsec;
    struct timeval tmptime1;
    struct timeval tmptime2;
    struct lwpinfo tmpinfo1; 
    struct lwpinfo tmpinfo2; 
    } myprof_t, * ptr_myprof_t;

void myprof_init(ptr_myprof_t);
void myprof_start(ptr_myprof_t);
void myprof_end(ptr_myprof_t);

#endif
