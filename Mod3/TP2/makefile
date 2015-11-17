tp2: main.c ag.c fb.c pd.c
	gcc -o tp2 main.c ag.c fb.c pd.c

pd:
	reset
	gcc -g -Wall -o tp2 main.c ag.c fb.c pd.c
	./tp2 -a PD

ag:
	reset
	gcc -g -Wall -o tp2 main.c ag.c fb.c pd.c
	./tp2 -a AG

fb:
	reset
	gcc -g -Wall -o tp2 main.c ag.c fb.c pd.c
	./tp2 -a FB

valpd:
	reset
	gcc -g -Wall -o tp2 main.c ag.c fb.c pd.c
	valgrind --leak-check=full --track-origins=yes ./tp2 -a PD

valag:
	reset
	gcc -g -Wall -o tp2 main.c ag.c fb.c pd.c
	valgrind --leak-check=full --track-origins=yes ./tp2 -a AG

valfb:
	reset
	gcc -g -Wall -o tp2 main.c ag.c fb.c pd.c
	valgrind --leak-check=full --track-origins=yes ./tp2 -a FB

clean:
	rm tp2