tp3: main.c funcoes.c
	gcc -o tp3 -lpthread main.c funcoes.c

run: main.c funcoes.c
	clear
	gcc -o tp3 -lpthread main.c funcoes.c
	./tp3 -t 4

val: main.c funcoes.c
	reset
	gcc -g -Wall -o tp3 -lpthread main.c funcoes.c
	valgrind ./tp3 -t 4

clean:
	rm tp3