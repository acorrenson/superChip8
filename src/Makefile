# set path to sdl here -> 
include_path = /usr/local/Cellar/sdl2/2.0.9_1/include/sdl2
lib_path_mac = /usr/local/Cellar/sdl2/2.0.9_1/lib/

test: main
	./main ../roms/brix.rom

auto_build: main.c utils.c system.c
	gcc main.c utils.c system.c -o main -l SDL2 -l m

main: main.c utils.c system.c
	gcc main.c utils.c system.c -o main -I ${include_path} -L ${lib_path_mac} -l SDL2 -l m

clean:
	rm -rf main
