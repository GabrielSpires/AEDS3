tp3: main.c funcoes.c
	gcc -o tp3 -pthread main.c funcoes.c

run: main.c funcoes.c
	clear
	gcc -o tp3 -pthread main.c funcoes.c
	./tp3 -t 18

val: main.c funcoes.c
	reset
	gcc -g -Wall -o tp3 -pthread main.c funcoes.c
	valgrind --leak-check=full --track-origins=yes ./tp3 -t 4

clean:
	rm tp3