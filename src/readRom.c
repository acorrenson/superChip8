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
        memory[i] = memory[i] | currentChar;
      }
    }
    i++;
  }

  fclose(f);

  return i;
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
  if(opCode == 0x00E0) {
    printf("CLS\n");
  }
  else if(opCode == 0x00EE) {
    printf("RET\n");
  }
  else if(opCode >> 12 == 1) {
    printf("JP\n");
  }
  else if(opCode >> 12 == 2) {
    printf("CALL\n");
  }
  else if(opCode >> 12 == 3) {
    printf("SKP\n");
  }
  else if(opCode >> 12 == 4) {
    printf("SKP\n");
  }
  else if(opCode >> 12 == 5) {
    printf("SKP\n");
  }
  else if(opCode >> 12 == 6) {
    printf("SET\n");
  }
  else if(opCode >> 12 == 7) {
    printf("ADD\n");
  }
  else if(opCode >> 12 == 8)
  {
    if ( (opCode & 0x0001) == 1) {
      printf("OR\n");
    }
    else if ( (opCode & 0x0002) == 2) {
      printf("AND\n");
    }
    else if ( (opCode & 0x0003) == 3) {
      printf("XOR\n");
    }
    else if ( (opCode & 0x0004) == 4) {
      printf("ADD\n");
    }
    else if ( (opCode & 0x0005) == 5) {
      printf("SUB\n");
    }
    else if ( (opCode & 0x0006) == 6) {
      printf("SHR\n");
    }
    else if ( (opCode & 0x0007) == 7) {
      printf("SUBN\n");
    }
    else if ( (opCode & 0x0008) == 8) {
      printf("SHL\n");
    }
  }
  else if (opCode >> 12 == 9) {
    printf("SKP\n");
  }
  else if (opCode >> 12 == 0xA) {
    printf("LD\n");
  }
  else if (opCode >> 12 == 0xB) {
    printf("JP\n");
  }
  else if (opCode >> 12 == 0xC) {
    printf("RND\n");
  }
  else if (opCode >> 12 == 0xD) {
    printf("DRW\n");
  }
  else if (opCode >> 12 == 0xE)
  {
    if ( (opCode & 0x009E) ==  0x009E ) {
      printf("SKP\n");
    }
    else if ( (opCode & 0x00A1) == 0x00A1 ) {
      printf("SKNP\n");
    }
  }
  else if (opCode >> 12 == 0xF ) {
    if ( (opCode & 0x0007) == 0x0007 ) {
      printf("LD\n");
    } else if ( (opCode & 0x000A) == 0x000A ) {
      // LD Vx, K
      printf("LD\n");
    } else if ( (opCode & 0x0015) == 0x0015 ) {
      // LD DT, Vx
      printf("LD\n");
    } else if ( (opCode & 0x0018) == 0x0018 ) {
      // LD ST, Vx
      printf("LD\n");
    } else if ( (opCode & 0x001E) == 0x001E ) {
      // ADD I, Vx
      printf("ADD\n");
    } else if ( (opCode & 0x0029) == 0x0029 ) {
      // LD F, Vx
      printf("LD\n");
    } else if ( (opCode & 0x0033) == 0x0033 ) {
      // LD B, Vx
      printf("LD\n");
    } else if ( (opCode & 0x0055) == 0x0055 ) {
      // LD [I], Vx
      printf("LD\n");
    } else if ( (opCode & 0x0065) == 0x0065 ) {
      // LD Vx, [I]
      printf("LD\n");
    }
  } else {
    printf("NOT FOUND %04x\n", opCode);
  }
}