tp1: main.c lista.c lista.h fila.c fila.h heap.c heap.h
	reset
	gcc -Wall -g -o tp1 main.c lista.c fila.c heap.c
	
run:
	reset
	./tp1

val:
	valgrind --track-origins=yes --leak-check=full ./tp1

clean:
	rm tp1
