tp2: main.c
	gcc -g -Wall -o tp2 main.c

pd:
	reset
	gcc -g -Wall -o tp2 main.c
	./tp2 -PD

ag:
	reset
	gcc -g -Wall -o tp2 main.c
	./tp2 -AG

fb:
	reset
	gcc -g -Wall -o tp2 main.c
	./tp2 -FB

valpd:
	reset
	gcc -g -Wall -o tp2 main.c
	valgrind --leak-check=full --track-origins=yes ./tp2 -PD

valag:
	reset
	gcc -g -Wall -o tp2 main.c
	valgrind --leak-check=full --track-origins=yes ./tp2 -AG

valfb:
	reset
	gcc -g -Wall -o tp2 main.c
	valgrind --leak-check=full --track-origins=yes ./tp2 -FB

clean:
	rm tp2