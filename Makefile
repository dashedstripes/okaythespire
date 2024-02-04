CC=gcc
SRC=main.c card.c deck.c

compile:
	$(CC) $(SRC) -F /Library/Frameworks -framework SDL2 -o bin/main.out -rpath /Library/Frameworks

run:
	./bin/main.out