tp3: main.c
	gcc -o tp3 -lpthread main.c

run: main.c
	gcc -o tp3 -lpthread main.c
	clear
	./tp3 -t 4

val: main.c
	gcc -g -Wall -o tp3 -lpthread main.c
	reset
	valgrind ./tp3 -t 4

clean:
	rm tp3