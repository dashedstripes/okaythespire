CC=gcc
SRC=main.c card.c hand.c deck.c player.c enemy.c

compile:
	$(CC) $(SRC) -F /Library/Frameworks -framework SDL2 -o bin/main.out -rpath /Library/Frameworks

run:
	./bin/main.out
