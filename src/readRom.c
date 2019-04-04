#include <stdio.h>

void readRom()
{
  FILE * f = fopen("/Users/arthur/Downloads/chip8-master/roms/15puzzle.rom", "r");

  unsigned char memory[4096];
  unsigned short opCode;
  int i = 0;

  while(!feof(f)) {
    char c = fgetc(f);
    if(c != '\n') {
      memory[i] = c;
    }
    i++;
  }

  for (int j = 0; j < i; j = j + 2) {
    opCode = memory[j] << 8 | memory[j+1];
    printf("opCode : %04X\n", opCode);
  }

  fclose(f);
}