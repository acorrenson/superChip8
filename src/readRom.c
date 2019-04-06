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
  unsigned char firstHalf;
  unsigned char secndHalf;
  int i = 0;

  while(!feof(f)) {
    firstHalf = fgetc(f);
    secndHalf = fgetc(f);
    memory[i] = (firstHalf << 8 | secndHalf);
    i++;
  }

  fclose(f);

  return i-1;
}

/**
 * @brief      Print the current state of the memory
 *
 * @param      memory  The memory
 * @param[in]  size    Number of opCodes
 */
void printMemory(unsigned short * memory, int size)
{
  for (int j = 0; j < size; j++) {
    printf("opCode n° %d: %04X\n", j+1, memory[j]);
  }
}

void desasembler(unsigned short const opCode)
{
  if(opCode == 0x00E0) {
    printf("opCode : %04X  | asembler : CLS\n", opCode);
  }
  else if(opCode == 0x00EE) {
    printf("opCode : %04X  | asembler : RET\n", opCode);
  }
  else if(opCode >> 12 == 1) {
    printf("opCode : %04X  | asembler : JP\n", opCode);
  }
  else if(opCode >> 12 == 2) {
    printf("opCode : %04X  | asembler : CALL\n", opCode);
  }
  else if(opCode >> 12 == 3) {
    printf("opCode : %04X  | asembler : SKP\n", opCode);
  }
  else if(opCode >> 12 == 4) {
    printf("opCode : %04X  | asembler : SKP\n", opCode);
  }
  else if(opCode >> 12 == 5) {
    printf("opCode : %04X  | asembler : SKP\n", opCode);
  }
  else if(opCode >> 12 == 6) {
    printf("opCode : %04X  | asembler : SET\n", opCode);
  }
  else if(opCode >> 12 == 7) {
    printf("opCode : %04X  | asembler : ADD\n", opCode);
  }
  else if(opCode >> 12 == 8)
  {
    if ( (opCode & 0x0000) == 0) {
      // LD Vx, Vy
      printf("opCode : %04X  | asembler : LD\n", opCode);
    }
    else if ( (opCode & 0x0001) == 1) {
      printf("opCode : %04X  | asembler : OR\n", opCode);
    }
    else if ( (opCode & 0x0002) == 2) {
      printf("opCode : %04X  | asembler : AND\n", opCode);
    }
    else if ( (opCode & 0x0003) == 3) {
      printf("opCode : %04X  | asembler : XOR\n", opCode);
    }
    else if ( (opCode & 0x0004) == 4) {
      printf("opCode : %04X  | asembler : ADD\n", opCode);
    }
    else if ( (opCode & 0x0005) == 5) {
      printf("opCode : %04X  | asembler : SUB\n", opCode);
    }
    else if ( (opCode & 0x0006) == 6) {
      printf("opCode : %04X  | asembler : SHR\n", opCode);
    }
    else if ( (opCode & 0x0007) == 7) {
      printf("opCode : %04X  | asembler : SUBN\n", opCode);
    }
    else if ( (opCode & 0x0008) == 8) {
      printf("opCode : %04X  | asembler : SHL\n", opCode);
    }
  }
  else if (opCode >> 12 == 9) {
    printf("opCode : %04X  | asembler : SKP\n", opCode);
  }
  else if (opCode >> 12 == 0xA) {
    printf("opCode : %04X  | asembler : LD\n", opCode);
  }
  else if (opCode >> 12 == 0xB) {
    printf("opCode : %04X  | asembler : JP\n", opCode);
  }
  else if (opCode >> 12 == 0xC) {
    printf("opCode : %04X  | asembler : RND\n", opCode);
  }
  else if (opCode >> 12 == 0xD) {
    printf("opCode : %04X  | asembler : DRW\n", opCode);
  }
  else if (opCode >> 12 == 0xE)
  {
    if ( (opCode & 0x009E) ==  0x009E ) {
      printf("opCode : %04X  | asembler : SKP\n", opCode);
    }
    else if ( (opCode & 0x00A1) == 0x00A1 ) {
      printf("opCode : %04X  | asembler : SKNP\n", opCode);
    }
  }
  else if (opCode >> 12 == 0xF ) {
    if ( (opCode & 0x0007) == 0x0007 ) {
      printf("opCode : %04X  | asembler : LD\n", opCode);
    } else if ( (opCode & 0x000A) == 0x000A ) {
      // LD Vx, K
      printf("opCode : %04X  | asembler : LD\n", opCode);
    } else if ( (opCode & 0x0015) == 0x0015 ) {
      // LD DT, Vx
      printf("opCode : %04X  | asembler : LD\n", opCode);
    } else if ( (opCode & 0x0018) == 0x0018 ) {
      // LD ST, Vx
      printf("opCode : %04X  | asembler : LD\n", opCode);
    } else if ( (opCode & 0x001E) == 0x001E ) {
      // ADD I, Vx
      printf("opCode : %04X  | asembler : ADD\n", opCode);
    } else if ( (opCode & 0x0029) == 0x0029 ) {
      // LD F, Vx
      printf("opCode : %04X  | asembler : LD\n", opCode);
    } else if ( (opCode & 0x0033) == 0x0033 ) {
      // LD B, Vx
      printf("opCode : %04X  | asembler : LD\n", opCode);
    } else if ( (opCode & 0x0055) == 0x0055 ) {
      // LD [I], Vx
      printf("opCode : %04X  | asembler : LD\n", opCode);
    } else if ( (opCode & 0x0065) == 0x0065 ) {
      // LD Vx, [I]
      printf("opCode : %04X  | asembler : LD\n", opCode);
    }
  } else {
    printf("opCode : %04X  | asembler : NOT FOUND\n", opCode);
  }
}