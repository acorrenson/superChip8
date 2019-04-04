#include <stdio.h>

/**
 * @brief      Reads a rom file.
 *
 * @param      memory  Pointer to the CHIP-8 memory
 * 
 * @return     Number of opCodes readen
 */
int readRom(unsigned short * memory, char * fileName)
{
  FILE * f = fopen(fileName, "r");

  unsigned short opCode;
  unsigned char currentChar;
  int i = 0;

  while(!feof(f)) {
    currentChar = fgetc(f);
    if(currentChar != '\n') {
      if (i%2 == 0) {
        // first half of the opCode
        memory[i] = (currentChar << 8);
      } else {
        // second half of the opCode
        memory[i-1] = memory[i-1] | currentChar;
      }
    }
    i++;
  }

  fclose(f);

  return i/2;
}

/**
 * @brief      Print the current state of the memory
 *
 * @param      memory  The memory
 * @param[in]  size    Number of opCodes
 */
void printMemory(unsigned short * memory, int size) {
  for (int j = 0; j < size; j = j + 1) {
    printf("opCode : %04X\n", memory[j]);
  }
}