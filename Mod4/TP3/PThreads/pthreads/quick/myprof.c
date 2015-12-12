
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "myprof.h"

void myprof_init(ptr_myprof_t m){
  m->elapsed.tv_sec = m->elapsed.tv_usec = 0;
  m->u_sec = m->u_nsec = m->s_sec = m->s_nsec = 0;
}

void myprof_start(ptr_myprof_t m){
  gettimeofday(&(m->tmptime1),(void*)0);
  _lwp_info(&(m->tmpinfo1));
}

#define NORMALIZE(s,u,m)   if (u < 0){ \
                            s--; \
                            u+=m; \
                           } else if (u>m){ \
                            s+=(u/m); \
                            u%=m; \
                           }


void myprof_end(ptr_myprof_t m){
  gettimeofday(&(m->tmptime2),(void*)0);
  _lwp_info(&(m->tmpinfo2));
  /* calculate the differences */
  m->elapsed.tv_sec += m->tmptime2.tv_sec - m->tmptime1.tv_sec;
  m->elapsed.tv_usec += m->tmptime2.tv_usec - m->tmptime1.tv_usec;
  NORMALIZE(m->elapsed.tv_sec,m->elapsed.tv_usec,1000000);
  m->u_sec += m->tmpinfo2.lwp_utime.tv_sec - m->tmpinfo1.lwp_utime.tv_sec; 
  m->u_nsec += m->tmpinfo2.lwp_utime.tv_nsec - m->tmpinfo1.lwp_utime.tv_nsec; 
  NORMALIZE(m->u_sec,m->u_nsec,1000000000);
  m->s_sec += m->tmpinfo2.lwp_stime.tv_sec - m->tmpinfo1.lwp_stime.tv_sec; 
  m->s_nsec += m->tmpinfo2.lwp_stime.tv_nsec - m->tmpinfo1.lwp_stime.tv_nsec; 
  NORMALIZE(m->s_sec,m->s_nsec,1000000000);
}


