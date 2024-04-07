CC=gcc
DIR=src/deb/usr/local/bin/numguesser
numguesser: src/*
	$(CC) -o $(DIR) src/main.c
	dpkg-deb --build src/deb/
	sudo dpkg -i src/*.deb
   # If executable symlink exists, remove and recreate. Otherwise, create normally.
	if [ -f /usr/bin/numguesser ] ;  then sudo rm -f /usr/bin/numguesser ; sudo ln -s /usr/local/bin/numguesser /usr/bin/numguesser ; else sudo ln -s /usr/local/bin/numguesser /usr/bin/numguesser ; fi

	
	