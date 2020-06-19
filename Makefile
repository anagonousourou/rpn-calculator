CC=gcc

Calculatrice: main.c calcul.c interface.c pilenpi.c pileoperateur.c verif.c
	$(CC) -o $@ $^ 