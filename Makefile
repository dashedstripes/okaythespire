CC=gcc
SRC=main.c card.c deck.c player.c enemy.c level.c text.c button.c

compile:
	$(CC) $(SRC) -F /Library/Frameworks -framework SDL2 -framework SDL2_image -framework SDL2_ttf -o bin/main.out -rpath /Library/Frameworks

compile-web:
	EMSDK_PYTHON=/opt/homebrew/bin/python3 emcc $(SRC) --use-port=sdl2 --use-port=sdl2_image --use-port=sdl2_ttf -o okaythespire.html

compile-mac:
	$(CC) -DMACOS_BUILD $(SRC) -F /Library/Frameworks -framework CoreFoundation -framework SDL2 -framework SDL2_image -framework SDL2_ttf -o bin/main.out -rpath /Library/Frameworks
	cp bin/main.out bin/mac/OkayTheSpire.app/Contents/MacOS/OkayTheSpire
	install_name_tool -delete_rpath /Library/Frameworks bin/mac/OkayTheSpire.app/Contents/MacOS/OkayTheSpire
	install_name_tool -add_rpath @executable_path/../Frameworks bin/mac/OkayTheSpire.app/Contents/MacOS/OkayTheSpire
run:
	./bin/main.out
