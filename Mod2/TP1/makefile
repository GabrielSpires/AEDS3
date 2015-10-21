tp1: main.c lista.c lista.h fila.c fila.h heap.c heap.h
	reset
	gcc -Wall -g -o tp1 main.c lista.c fila.c heap.c
	./tp1 < inputs/input.txt
	
run:
	reset
	./tp1 < inputs/input.txt

val:
	valgrind --track-origins=yes ./tp1 < inputs/input.txt

clean:
	rm tp1
