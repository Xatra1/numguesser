CC=gcc
numguesser: src/main.c src/funcs.h
	$(CC) -o numguesser src/main.c