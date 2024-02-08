CC=gcc
SRC=main.c card.c hand.c deck.c player.c enemy.c level.c

compile:
	$(CC) $(SRC) -F /Library/Frameworks -framework SDL2 -framework SDL2_image -framework SDL2_ttf -o bin/main.out -rpath /Library/Frameworks

run:
	./bin/main.out
