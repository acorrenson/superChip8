CC=gcc
SRC=$(wildcard src/*.c)

test: chip8
	./chip8 ./roms/brix.rom

chip8: ${SRC}
	${CC} ${SRC} -o chip8 -l SDL2 -l m

clean:
	rm -rf chip8
