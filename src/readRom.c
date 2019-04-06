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

/**
 * @brief      Pretty print an opCode and its assembly in stdin
 *
 * @param      instruction  The assembly instruction
 * @param[in]  opCode       The operation code
 */
void printOpCode(char * instruction, unsigned short const opCode)
{
  printf("OP_CODE : \033[35m%04X\033[0m  |  ASEMBLY : \033[35m%s\033[0m\n", opCode, instruction);
}

/**
 * @brief      Convert an opCode into assembly
 *
 * @param[in]  opCode  The operation code
 */
void desasembler(unsigned short const opCode)
{
  if(opCode == 0x00E0) {
    printOpCode("CLS", opCode);
  }
  else if(opCode == 0x00EE) {
    printOpCode("RET", opCode);
  }
  else if(opCode >> 12 == 0) {
    printOpCode("DEPRECATED SYS CALL", opCode);
  }
  else if(opCode >> 12 == 1) {
    printOpCode("JP", opCode);
  }
  else if(opCode >> 12 == 2) {
    printOpCode("CALL", opCode);
  }
  else if(opCode >> 12 == 3) {
    printOpCode("SKP", opCode);
  }
  else if(opCode >> 12 == 4) {
    printOpCode("SKP", opCode);
  }
  else if(opCode >> 12 == 5) {
    printOpCode("SKP", opCode);
  }
  else if(opCode >> 12 == 6) {
    printOpCode("SET", opCode);
  }
  else if(opCode >> 12 == 7) {
    printOpCode("ADD", opCode);
  }
  else if(opCode >> 12 == 8)
  {
    if ( (opCode & 0x0000) == 0) {
      // LD Vx, Vy
      printOpCode("LD", opCode);
    }
    else if ( (opCode & 0x0001) == 1) {
      printOpCode("OR", opCode);
    }
    else if ( (opCode & 0x0002) == 2) {
      printOpCode("AND", opCode);
    }
    else if ( (opCode & 0x0003) == 3) {
      printOpCode("XOR", opCode);
    }
    else if ( (opCode & 0x0004) == 4) {
      printOpCode("ADD", opCode);
    }
    else if ( (opCode & 0x0005) == 5) {
      printOpCode("SUB", opCode);
    }
    else if ( (opCode & 0x0006) == 6) {
      printOpCode("SHR", opCode);
    }
    else if ( (opCode & 0x0007) == 7) {
      printOpCode("SUBN", opCode);
    }
    else if ( (opCode & 0x0008) == 8) {
      printOpCode("SHL", opCode);
    }
  }
  else if (opCode >> 12 == 9) {
    printOpCode("SKP", opCode);
  }
  else if (opCode >> 12 == 0xA) {
    printOpCode("LD", opCode);
  }
  else if (opCode >> 12 == 0xB) {
    printOpCode("JP", opCode);
  }
  else if (opCode >> 12 == 0xC) {
    printOpCode("RND", opCode);
  }
  else if (opCode >> 12 == 0xD) {
    printOpCode("DRW", opCode);
  }
  else if (opCode >> 12 == 0xE)
  {
    if ( (opCode & 0x009E) ==  0x009E ) {
      printOpCode("SKP", opCode);
    }
    else if ( (opCode & 0x00A1) == 0x00A1 ) {
      printOpCode("SKNP", opCode);
    }
  }
  else if (opCode >> 12 == 0xF ) {
    if ( (opCode & 0x0007) == 0x0007 ) {
      printOpCode("LD", opCode);
    } else if ( (opCode & 0x000A) == 0x000A ) {
      // LD Vx, K
      printOpCode("LD", opCode);
    } else if ( (opCode & 0x0015) == 0x0015 ) {
      // LD DT, Vx
      printOpCode("LD", opCode);
    } else if ( (opCode & 0x0018) == 0x0018 ) {
      // LD ST, Vx
      printOpCode("LD", opCode);
    } else if ( (opCode & 0x001E) == 0x001E ) {
      // ADD I, Vx
      printOpCode("ADD", opCode);
    } else if ( (opCode & 0x0029) == 0x0029 ) {
      // LD F, Vx
      printOpCode("LD", opCode);
    } else if ( (opCode & 0x0033) == 0x0033 ) {
      // LD B, Vx
      printOpCode("LD", opCode);
    } else if ( (opCode & 0x0055) == 0x0055 ) {
      // LD [I], Vx
      printOpCode("LD", opCode);
    } else if ( (opCode & 0x0065) == 0x0065 ) {
      // LD Vx, [I]
      printOpCode("LD", opCode);
    }
  } else {
    printOpCode("NOT FOUND", opCode);
  }
}