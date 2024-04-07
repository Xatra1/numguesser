CC=gcc
DIR=src/deb/usr/local/bin/numguesser
numguesser: src/*
	$(CC) -o $(DIR) src/main.c
	dpkg-deb --build src/deb/
	sudo dpkg -i src/*.deb

	
	