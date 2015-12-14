tp3: main.c funcoes.c
	gcc -o tp -pthread main.c funcoes.c

run: main.c funcoes.c
	clear
	gcc -o tp -pthread main.c funcoes.c
	./tp -t 20

val: main.c funcoes.c
	reset
	gcc -g -Wall -o tp -pthread main.c funcoes.c
	valgrind --leak-check=full --track-origins=yes ./tp -t 10

clean:
	rm tp