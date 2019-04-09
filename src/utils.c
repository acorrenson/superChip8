#include <stdio.h>

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
void desasembler(unsigned short opCode, unsigned char V[16], unsigned short I, unsigned short stack[48], unsigned short stackPtr)
{

  unsigned short nnn = opCode & 0x0FFF;
  unsigned char x = (opCode & 0x0F00) >> 8;
  unsigned char y = (opCode & 0x00F0) >> 4;
  unsigned char n = opCode & 0x000F;
  unsigned short kk = opCode & 0x00FF;

  if (opCode == 0x00E0){
    printf("%04X - CLS\n", opCode);
  }

  else if (opCode == 0x00EE) {
    printf("%04X - RET [nw PC = %d]\n", opCode, stack[stackPtr]);
  }
  
  else if (opCode >> 12 == 0x0) {
    printf("%04X - DEPRECATED SYS CALL\n", opCode);
  }
  
  else if ((opCode & 0xF000) == 0x1000) {
    printf("%04X - JP %d\n", opCode, nnn);
  }
  
  else if ((opCode & 0xF000) == 0x2000) {
    printf("%04X - CALL %d\n", opCode, nnn);
  }
  
  else if ((opCode & 0xF000) == 0x3000) {
    printf("%04X - SE V%d (%d) %d\n", opCode, x, V[x], kk);
  }
  
  else if ((opCode & 0xF000) == 0x4000) {
    printf("%04X - SNE_Vx_byte\n", opCode);
  }
  
  else if ((opCode & 0xF00F) == 0x5000) {
    printf("%04X - SE V%d (%d) V%d (%d)\n", opCode, x, V[x], y, V[y]);
  }
  
  else if ((opCode & 0xF000) == 0x6000) {
    printf("%04X - LD V%d (%d) %d\n", opCode, x, V[x], kk);
  }
  
  else if ((opCode & 0xF000) == 0x7000) {
    printf("%04X - ADD V%d (%d) %d\n", opCode, x, V[x], kk);
  }

  else if ((opCode & 0xF00F) == 0x8000) {
    printf("%04X - LD V%d (%d) V%d %d\n", opCode, x, V[x], y, V[y]);
  }
  
  else if ((opCode & 0xF00F) == 0x8001) {
    printf("%04X - OR_Vx_Vy\n", opCode);
  }
  
  else if ((opCode & 0xF00F) == 0x8002) {
    printf("%04X - AND_Vx_Vy\n", opCode);
  }
  
  else if ((opCode & 0xF00F) == 0x8003) {
    printf("%04X - XOR_Vx_Vy\n", opCode);
  }
  
  else if ((opCode & 0xF00F) == 0x8004) {
    printf("%04X - ADD V%d (%d) V%d (%d) \n", opCode, x, V[x], y, V[y]);
  }
  
  else if ((opCode & 0xF00F) == 0x8005) {
    printf("%04X - SUB Vx - Vy\n", opCode);
  }
  
  else if ((opCode & 0xF00F) == 0x8006) {
    printf("%04X - SHR Vx\n", opCode);
  }
  
  else if ((opCode & 0xF00F) == 0x8007) {
    printf("%04X - SUNB Vx Vy\n", opCode);
  }
  
  else if ((opCode & 0xF00F) == 0x800E) {
    printf("%04X - SHL Vx\n", opCode);
  }
  
  else if ((opCode & 0xF00F) == 0x9000) {
    printf("%04X - SNE V%d (%d) V%d (%d)\n", opCode, x, V[x], y, V[y]);
  }
  
  else if ((opCode & 0xF000) == 0xA000) {
    printf("%04X - LD I %d [set I = %d]\n", opCode, nnn, nnn);
  }
  
  else if ((opCode & 0xF000) == 0xB000) {
    printf("%04X - JP V%d (%d)  + %d\n", opCode, x, V[x], nnn);
  }
  
  else if ((opCode & 0xF000) == 0xC000) {
    printf("%04X - RND\n", opCode);
  }
  
  else if ((opCode & 0xF000) == 0xD000) {
    printf("%04X - DRW %d\n", opCode, I);        
  }
  
  else if ((opCode & 0xF0FF) == 0xE09E) {
    printf("%04X - SKP K\n", opCode);
  }
  
  else if ((opCode & 0xF0FF) == 0xE0A1) {
    printf("%04X - SKNP Vx\n", opCode);
  }
  
  else if ((opCode & 0xF0FF) == 0xF007) {
    printf("%04X - LD_Vx_DT\n", opCode);
  }
  
  else if ((opCode & 0xF0FF) == 0xF00A) {
    printf("%04X - LD_Vx_K\n", opCode);
  }
  
  else if ((opCode & 0xF0FF) == 0xF015) {
    printf("%04X - LD_DT_Vx\n", opCode);
  }
  
  else if ((opCode & 0xF0FF) == 0xF018) {
    printf("%04X - LD_ST_Vx\n", opCode);
  }
  
  else if ((opCode & 0xF0FF) == 0xF01E) {
    printf("%04X - ADD I (%d) V%d (%d)\n", opCode, I, x, V[x]);
  }
  
  else if ((opCode & 0xF0FF) == 0xF029) {
    printf("%04X - LD F V%d (%d) [set I to %d]\n", opCode, x, V[x], V[x]*5);
  }
  
  else if ((opCode & 0xF0FF) == 0xF033) {
    printf("%04X - LD B\n", opCode);
  }
  
  else if ((opCode & 0xF0FF) == 0xF055) {
    printf("%04X - LD I V%d (%d) [set mem %d-%d]\n", opCode, x, V[x], I, I+x);
  }
  
  else if ((opCode & 0xF0FF) == 0xF065) {
    printf("%04X - LD V%d (%d) I [set reg %d-%d]\n", opCode, x, V[x], 0, x);
  }
}
