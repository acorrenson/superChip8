#include <stdio.h>
#include <SDL2/SDL.h>
#include "instructions.h"


unsigned short getOpCodeAt(unsigned char * memoryPtr, unsigned char programCounter)
{
  unsigned char firstHalf = memoryPtr[programCounter];
  unsigned char secndHalf = memoryPtr[programCounter+1];
  unsigned short opCode = (firstHalf << 8 | secndHalf);
  return opCode;
}

/**
 * @brief      Reads a rom file.
 *
 * @param      memory  Pointer to the CHIP-8 memory
 * 
 * @return     Number of opCodes readen
 */
int readRom(unsigned char * memory, char const * fileName)
{
  FILE * f = fopen(fileName, "r");

  
  int i = 0;

  while(!feof(f)) {
    memory[i] = fgetc(f);
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
void printMemory(unsigned char * memory, int size)
{
  for (int j = 0; j < size; j++) {
    printf("mem slot n° %d: %02X\n", j+1, memory[j]);
  }
}

/**
 * @brief      Convert an opCode into assembly
 *
 * @param[in]  opCode  The operation code
 */
void desasembler(unsigned short const opCode, 
                 unsigned char *pProgramCounter,
                 unsigned char V[16], 
                 unsigned short *pI, 
                 unsigned char stack[48], 
                 unsigned short *pStackPtr,
                 SDL_Renderer *renderer,
                 unsigned char screen[32][64],
                 int keyBoardState[16],
                 unsigned char memory[4096],
                 unsigned short * pDelayTimer,
                 unsigned short * pSoundTimer)
{
  if(opCode == 0x00E0) {
    CLS(opCode, pProgramCounter, renderer, screen);
  }
  else if(opCode == 0x00EE) {
    RET(opCode, pProgramCounter, stack, pStackPtr);
  }
  else if(opCode >> 12 == 0) {
    printf("%04X - DEPRECATED SYS CALL\n", opCode);
  }
  else if(opCode >> 12 == 1) {
    JP_addr(opCode, pProgramCounter);
  }
  else if(opCode >> 12 == 2) {
    CALL_addr(opCode, pProgramCounter, stack, pStackPtr);
  }
  else if(opCode >> 12 == 3) {
    SE_Vx_byte(opCode, pProgramCounter, V);
  }
  else if(opCode >> 12 == 4) {
    SNE_Vx_byte(opCode, pProgramCounter, V);
  }
  else if(opCode >> 12 == 5) {
    SE_Vx_Vy(opCode, pProgramCounter, V);
  }
  else if(opCode >> 12 == 6) {
    LD_Vx_byte(opCode, pProgramCounter, V);
  }
  else if(opCode >> 12 == 7) {
    ADD_Vx_byte(opCode, pProgramCounter, V);
  }
  else if(opCode >> 12 == 8)
  {
    if ( (opCode & 0x0000) == 0) {
      LD_Vx_Vy(opCode, pProgramCounter, V);
    }
    else if ( (opCode & 0x0001) == 1) {
      OR_Vx_Vy(opCode, pProgramCounter, V);
    }
    else if ( (opCode & 0x0002) == 2) {
      AND_Vx_Vy(opCode, pProgramCounter, V);
    }
    else if ( (opCode & 0x0003) == 3) {
      XOR_Vx_Vy(opCode, pProgramCounter, V);
    }
    else if ( (opCode & 0x0004) == 4) {
      ADD_Vx_Vy(opCode, pProgramCounter, V);
    }
    else if ( (opCode & 0x0005) == 5) {
      SUB_Vx_Vy(opCode, pProgramCounter, V);
    }
    else if ( (opCode & 0x0006) == 6) {
      SHR_Vx(opCode, pProgramCounter, V);
    }
    else if ( (opCode & 0x0007) == 7) {
      SUBN_Vx_Vy(opCode, pProgramCounter, V);
    }
    else if ( (opCode & 0x0008) == 8) {
      SHL_Vx(opCode, pProgramCounter, V);
    }
  }
  else if (opCode >> 12 == 9) {
    SNE_Vx_Vy(opCode, pProgramCounter, V);
  }
  else if (opCode >> 12 == 0xA) {
    LD_I_addr(opCode, pProgramCounter, pI);
  }
  else if (opCode >> 12 == 0xB) {
    JP_V0_addr(opCode, pProgramCounter, V);
  }
  else if (opCode >> 12 == 0xC) {
    RND_Vx_byte(opCode, pProgramCounter, V);
  }
  else if (opCode >> 12 == 0xD) {
    DRW_Vx_Vy_nibble(opCode, pProgramCounter, V, pI, screen, memory);
  }
  else if (opCode >> 12 == 0xE)
  {
    if ( (opCode & 0x009E) ==  0x009E ) {
      SKP_Vx(opCode, pProgramCounter, V, keyBoardState);
    }
    else if ( (opCode & 0x00A1) == 0x00A1 ) {
      SKNP_Vx(opCode, pProgramCounter, V, keyBoardState);
    }
  }
  else if (opCode >> 12 == 0xF ) {
    if ( (opCode & 0x0007) == 0x0007 ) {
      LD_Vx_DT(opCode, pProgramCounter, V, pDelayTimer);
    } else if ( (opCode & 0x000A) == 0x000A ) {
      LD_Vx_K(opCode, pProgramCounter, V, keyBoardState);
    } else if ( (opCode & 0x0015) == 0x0015 ) {
      LD_DT_Vx(opCode, pProgramCounter, V, pDelayTimer);
    } else if ( (opCode & 0x0018) == 0x0018 ) {
      LD_ST_Vx(opCode, pProgramCounter, V, pSoundTimer);
    } else if ( (opCode & 0x001E) == 0x001E ) {
      ADD_I_Vx(opCode, pProgramCounter, V, pI);
    } else if ( (opCode & 0x0029) == 0x0029 ) {
      LD_F_Vx(opCode, pProgramCounter, V, pI);
    } else if ( (opCode & 0x0033) == 0x0033 ) {
      LD_B_Vx(opCode, pProgramCounter, V, pI, memory);
    } else if ( (opCode & 0x0055) == 0x0055 ) {
      LD_I_Vx(opCode, pProgramCounter, V, pI, memory);
    } else if ( (opCode & 0x0065) == 0x0065 ) {
      LD_Vx_I(opCode, pProgramCounter, V, pI, memory);
    }
  } else {
    printf("NOT FOUND : %04x", opCode);
  }
}
