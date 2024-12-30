CC=gcc
numguesser: src/*
	$(CC) -o numguesser src/main.c
