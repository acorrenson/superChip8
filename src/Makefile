# set path to sdl here -> 
include_path = /usr/local/Cellar/sdl2/2.0.9_1/include/sdl2
lib_path_mac = /usr/local/Cellar/sdl2/2.0.9_1/lib/

test: main
	./main ../roms/15puzzle.rom

main: main.c readRom.c
	gcc main.c readRom.c -o main -I ${include_path} -L ${lib_path_mac} -l SDL2