CC=gcc

compile:
	$(CC) main.c -o bin/main.out -F frameworks -framework SDL2 -rpath @executable_path/../frameworks

run:
	./bin/main.out