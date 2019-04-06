#include <stdio.h>

/**
 * @brief      Reads a rom file.
 *
 * @param      memory  Pointer to the CHIP-8 memory
 * 
 * @return     Number of opCodes readen
 */
int readRom(unsigned short * memory, char const * fileName)
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
void printMemory(unsigned short * memory, int size)
{
  for (int j = 0; j < size; j = j + 1) {
    printf("opCode : %04X\n", memory[j]);
  }
}

void desasembler(unsigned short const opCode)
{
  if(opCode == 0x00E0)
    printf("CLS\n");
  else if(opCode == 0x00EE)
    printf("RET\n");
  else if(opCode >> 12 == 1)
    printf("JP\n");
  else if(opCode >> 12 == 2)
    printf("CALL\n");
  else if(opCode >> 12 == 3)
    printf("SKP\n");
  else if(opCode >> 12 == 4)
    printf("SKP\n");
  else if(opCode >> 12 == 5)
    printf("SKP\n");
  else if(opCode >> 12 == 6)
    printf("SET\n");
  else if(opCode >> 12 == 7)
    printf("ADD\n");
  else if(opCode >> 12 == 8)
  {
    if ( opCode & 0x0001 == 1) 
      printf("OR\n");
    if ( opCode & 0x0002 == 2)
      printf("AND\n");
    if ( opCode & 0x0003 == 3)
      printf("XOR\n");
    if ( opCode & 0x0004 == 4)
      printf("ADD\n");
    if ( opCode & 0x0005 == 5)
      printf("SUB\n");
    if ( opCode & 0x0006 == 6)
      printf("SHR\n");
    if ( opCode & 0x0007 == 7)
      printf("SUBN\n");
    if ( opCode & 0x0008 == 8)
      printf("SHL\n");
  }
  else if(opCode >> 12 == 9)
    printf("SKP\n");
  else if(opCode >> 12 == 0xA)
    printf("LD\n");
  else if(opCode >> 12 == 0xB)
    printf("JP\n");
  else if(opCode >> 12 == 0xC)
    printf("RND\n");
  else if(opCode >> 12 == 0xD)
    printf("DRW\n");
  else if(opCode >> 12 == 0xE)
  {
    
      printf("DRW\n");
  }





}