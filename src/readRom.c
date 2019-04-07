#include <stdio.h>
#include <SDL2/SDL.h>
#include "instructions.h"

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
 * @brief      Convert an opCode into assembly
 *
 * @param[in]  opCode  The operation code
 */
void desasembler(unsigned short const opCode, 
                 unsigned short *pProgramCounter, 
                 unsigned char V[16], 
                 unsigned short *pI, 
                 unsigned char stack[48], 
                 unsigned short *pStackPtr, 
                 SDL_Renderer *renderer)
{
  if(opCode == 0x00E0) {
    CLS(opCode);
  }
  else if(opCode == 0x00EE) {
    RET(opCode);
  }
  else if(opCode >> 12 == 0) {
    printf("%04X - DEPRECATED SYS CALL\n", opCode);
  }
  else if(opCode >> 12 == 1) {
    JP_addr(opCode);
  }
  else if(opCode >> 12 == 2) {
    CALL_addr(opCode);
  }
  else if(opCode >> 12 == 3) {
    SE_Vx_byte(opCode);
  }
  else if(opCode >> 12 == 4) {
    SNE_Vx_byte(opCode);
  }
  else if(opCode >> 12 == 5) {
    SE_Vx_Vy(opCode);
  }
  else if(opCode >> 12 == 6) {
    LD_Vx_byte(opCode);
  }
  else if(opCode >> 12 == 7) {
    ADD_Vx_byte(opCode);
  }
  else if(opCode >> 12 == 8)
  {
    if ( (opCode & 0x0000) == 0) {
      LD_Vx_Vy(opCode);
    }
    else if ( (opCode & 0x0001) == 1) {
      OR_Vx_Vy(opCode);
    }
    else if ( (opCode & 0x0002) == 2) {
      AND_Vx_Vy(opCode);
    }
    else if ( (opCode & 0x0003) == 3) {
      XOR_Vx_Vy(opCode);
    }
    else if ( (opCode & 0x0004) == 4) {
      ADD_Vx_Vy(opCode);
    }
    else if ( (opCode & 0x0005) == 5) {
      SUB_Vx_Vy(opCode);
    }
    else if ( (opCode & 0x0006) == 6) {
      SHR_Vx(opCode);
    }
    else if ( (opCode & 0x0007) == 7) {
      SUBN_Vx_Vy(opCode);
    }
    else if ( (opCode & 0x0008) == 8) {
      SHL_Vx(opCode);
    }
  }
  else if (opCode >> 12 == 9) {
    SNE_Vx_Vy(opCode);
  }
  else if (opCode >> 12 == 0xA) {
    LD_I_addr(opCode);
  }
  else if (opCode >> 12 == 0xB) {
    JP_V0_addr(opCode);
  }
  else if (opCode >> 12 == 0xC) {
    RND_Vx_byte(opCode);
  }
  else if (opCode >> 12 == 0xD) {
    DRW_Vx_Vy_nibble(opCode);
  }
  else if (opCode >> 12 == 0xE)
  {
    if ( (opCode & 0x009E) ==  0x009E ) {
      SKP_Vx(opCode);
    }
    else if ( (opCode & 0x00A1) == 0x00A1 ) {
      SKNP_Vx(opCode);
    }
  }
  else if (opCode >> 12 == 0xF ) {
    if ( (opCode & 0x0007) == 0x0007 ) {
      LD_Vx_DT(opCode);
    } else if ( (opCode & 0x000A) == 0x000A ) {
      LD_Vx_K(opCode);
    } else if ( (opCode & 0x0015) == 0x0015 ) {
      LD_DT_Vx(opCode);
    } else if ( (opCode & 0x0018) == 0x0018 ) {
      LD_ST_Vx(opCode);
    } else if ( (opCode & 0x001E) == 0x001E ) {
      ADD_I_Vx(opCode);
    } else if ( (opCode & 0x0029) == 0x0029 ) {
      LD_F_Vx(opCode);
    } else if ( (opCode & 0x0033) == 0x0033 ) {
      LD_B_Vx(opCode);
    } else if ( (opCode & 0x0055) == 0x0055 ) {
      LD_I_Vx(opCode);
    } else if ( (opCode & 0x0065) == 0x0065 ) {
      LD_Vx_I(opCode);
    }
  } else {
    printf("NOT FOUND : %04x", opCode);
  }
}
