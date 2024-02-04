CC=gcc

compile:
	$(CC) main.c -F /Library/Frameworks -framework SDL2 -o bin/main.out -rpath /Library/Frameworks

run:
	./bin/main.out