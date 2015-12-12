# Algoritmo de Ordenacao  - Quicksort
# Bruno Diniz de Paula - LCP/UFMG

CC      = gcc
CFLAGS  = -g -Wall
CCFLAGS = -lpthread -lposix4
OBJS    = QuickParallel.o barrier.o newsem.o myprof.o
LIBS    = -lm

all:       QuickParallel

QuickParallel:   $(OBJS)
	$(CC) $(OBJS) $(CCFLAGS) $(LIBS) -o $@

QuickParallel.o:  QuickParallel.c
	$(CC) $(CFLAGS) -c QuickParallel.c

barrier.o: barrier.h
barrier.o: barrier.c
	$(CC) $(CFLAGS) -c barrier.c

newsem.o: newsem.h
newsem.o: newsem.c
	$(CC) $(CFLAGS) -c newsem.c

myprof.o: myprof.h
myprof.o: myprof.c
	$(CC) $(CFLAGS) -c myprof.c

clean:
	rm -f *.o *~ core QuickParallel
