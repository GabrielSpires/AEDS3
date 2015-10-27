tp2: main.c
	gcc -g -Wall -o tp2 main.c

p:
	./tp2 -PD

g:
	./tp2 -AG

f:
	./tp2 -FB

valp:
	reset
	valgrind --leak-check=full --track-origins=yes ./tp2 -PD

valg:
	reset
	valgrind --leak-check=full --track-origins=yes ./tp2 -AG

valf:
	reset
	valgrind --leak-check=full --track-origins=yes ./tp2 -FB

clean:
	rm tp2