#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "system.h"

// -- CHIP-8 INSTRUCTIONS --

void CLS(unsigned short const opCode, unsigned short *pProgramCounter, SDL_Renderer *renderer)
{
    // Print assembler code
    printf("%04X - CLS\n", opCode);
    // Op
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    ++ *pProgramCounter;
}

void RET(unsigned short const opCode, unsigned short *pProgramCounter, unsigned char stack[48], unsigned short *pStack)
{
    // Print assembler code
    printf("%04X - RET\n", opCode);
    // Op
    *pProgramCounter = stack[*pStack];
    -- *pStack;
}

void JP_addr(unsigned short const opCode, unsigned short *pProgramCounter)
{
    // Filter
    unsigned short addr;
    addr = opCode & 0x0FFF;
    // Print assembler code
    printf("%04X - JP    #%04X\n", opCode, addr);
    // Op
    *pProgramCounter = addr;
}

void CALL_addr(unsigned short const opCode, unsigned short *pProgramCounter, unsigned char stack[48], unsigned short *pStack)
{
    // Filter
    unsigned short addr;
    addr = opCode & 0x0FFF;
    // Print assembler code
    printf("%04X - CALL  #%04X\n", opCode, addr);
    // Op
    ++ *pStack;
    stack[*pStack] = *pProgramCounter;
    *pProgramCounter = addr;
}

void SE_Vx_byte(unsigned short const opCode, unsigned short *pProgramCounter, unsigned char V[16])
{
    //Filter
    unsigned char Vx;
    unsigned short kk;
    Vx = (opCode & 0x0F00) >> 8;
    kk = opCode & 0x00FF;
    // Print assembler code
    printf("%04X - SE    V%u, #%x\n", opCode, Vx, kk);
    // Op
    if (V[Vx] == kk)
        *pProgramCounter += 2;
    else
        ++ *pProgramCounter;
}

void SNE_Vx_byte(unsigned short const opCode, unsigned short *pProgramCounter, unsigned char V[16])
{
    // Filter
    unsigned char Vx;
    unsigned short kk;
    Vx = (opCode & 0x0F00) >> 8;
    kk = opCode & 0x00FF;
    // Print assembler code
    printf("%04X - SNE   V%u, #%x\n", opCode, Vx, kk);
    // Op
    if (V[Vx] != kk)
        *pProgramCounter += 2;
    else
        ++ *pProgramCounter;
}

void SE_Vx_Vy(unsigned short const opCode, unsigned short *pProgramCounter, unsigned char V[16])
{
    // Filter
    unsigned char Vx, Vy;
    Vx = (opCode & 0x0F00) >> 8;
    Vy = (opCode & 0x00F0) >> 4;
    // Print assembler code
    printf("%04X - SE    V%u, V%u\n", opCode, Vx, Vy);
    // Op
    if (V[Vx] == V[Vy])
        *pProgramCounter += 2;
    else
        ++ *pProgramCounter;
}

void LD_Vx_byte(unsigned short const opCode, unsigned short *pProgramCounter, unsigned char V[16])
{
    // Filter
    unsigned char Vx;
    unsigned short kk;
    Vx = (opCode & 0x0F00) >> 8; 
    kk = opCode & 0x00FF;
    // Print assembler code
    printf("%04X - LD    V%u, #%x\n", opCode, Vx, kk);
    // Op
    V[Vx] = kk;
    ++ *pProgramCounter;
}

void ADD_Vx_byte(unsigned short const opCode, unsigned short *pProgramCounter, unsigned char V[16])
{
    // Filter
    unsigned char Vx;
    unsigned short kk;
    Vx = (opCode & 0x0F00) >> 8;
    kk = opCode & 0x00FF;
    // Print assembler code
    printf("%04X - ADD   V%u, #%x\n", opCode, Vx, kk);
    // Op
    V[Vx] += kk;
    ++ *pProgramCounter;
}

void LD_Vx_Vy(unsigned short const opCode, unsigned short *pProgramCounter, unsigned char V[16])
{
    // Filter
    unsigned char Vx, Vy;
    Vx = (opCode & 0x0F00) >> 8;
    Vy = (opCode & 0x00F0) >> 4;
    // Print assembler code
    printf("%04X - LD    V%u, V%u\n", opCode, Vx, Vy);
    // Op
    V[Vx] = V[Vy];
    ++ *pProgramCounter;
}

void OR_Vx_Vy(unsigned short const opCode, unsigned short *pProgramCounter, unsigned char V[16])
{
    // Filter
    unsigned char Vx, Vy;
    Vx = (opCode & 0x0F00) >> 8;
    Vy = (opCode & 0x00F0) >> 4;
    // Print assembler code
    printf("%04X - OR    V%u, V%u\n", opCode, Vx, Vy);
    // Op
    V[Vx] = V[Vx] | V[Vy];
    ++ *pProgramCounter;
}

void AND_Vx_Vy(unsigned short const opCode, unsigned short *pProgramCounter, unsigned char V[16])
{
    // Filter
    unsigned char Vx, Vy;
    Vx = (opCode & 0x0F00) >> 8;
    Vy = (opCode & 0x00F0) >> 4;
    // Print assembler code
    printf("%04X - AND   V%u, V%u\n", opCode, Vx, Vy);
    // Op
    // var: V
    V[Vx] = V[Vx] & V[Vy];
    ++ *pProgramCounter;
}

void XOR_Vx_Vy(unsigned short const opCode, unsigned short *pProgramCounter, unsigned char V[16])
{
    // Filter
    unsigned char Vx, Vy;
    Vx = (opCode & 0x0F00) >> 8; 
    Vy = (opCode & 0x00F0) >> 4;
    // Print assembler code
    printf("%04X - XOR   V%u, V%u\n", opCode, Vx, Vy);
    // Op
    // var: V
    V[Vx] = V[Vx] ^ V[Vy];
    ++ *pProgramCounter;
}

void ADD_Vx_Vy(unsigned short const opCode, unsigned short *pProgramCounter, unsigned char V[16])
{
    // Filter
    unsigned char Vx, Vy;
    Vx = (opCode & 0x0F00) >> 8;
    Vy = (opCode & 0x00F0) >> 4;
    // Print assembler code
    printf("%04X - ADD   V%u, V%u\n", opCode, Vx, Vy);
    // Op
    unsigned short temp;
    temp = V[Vx] + V[Vy];
    if (temp > 255)
        V[15] = 1;
    V[Vx] = (temp & 0x00FF);
    ++ *pProgramCounter;
}

void SUB_Vx_Vy(unsigned short const opCode, unsigned short *pProgramCounter, unsigned char V[16])
{
    // Filter
    unsigned char Vx, Vy;
    Vx = (opCode & 0x0F00) >> 8;
    Vy = (opCode & 0x00F0) >> 4;
    // Print assembler code
    printf("%04X - SUB   V%u, V%u\n", opCode, Vx, Vy);
    // Op
    if (V[Vx] > V[Vy])
        V[15] = 1;
    else
        V[15] = 0;
    V[Vx] = V[Vx] - V[Vy];
    ++ *pProgramCounter;
}

void SHR_Vx(unsigned short const opCode, unsigned short *pProgramCounter, unsigned char V[16])
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04X - SHR   V%u\n", opCode, Vx);
    // Op
    if ((V[Vx] << 7) != 0)
        V[15] = 1;
    else
        V[15] = 0;
    V[Vx] = (V[Vx] >> 1) + V[15];
    ++ *pProgramCounter;
}

void SUBN_Vx_Vy(unsigned short const opCode, unsigned short *pProgramCounter, unsigned char V[16])
{
    // Filter
    unsigned char Vx, Vy;
    Vx = (opCode & 0x0F00) >> 8;
    Vy = (opCode & 0x00F0) >> 4;
    // Print assembler code
    printf("%04X - SUBN  V%u, V%u\n", opCode, Vx, Vy);
    // Op
    if (V[Vy] > V[Vx])
        V[15] = 1;
    else
        V[15] = 0;
    V[Vx] = V[Vy] - V[Vx];
    ++ *pProgramCounter;
}

void SHL_Vx(unsigned short const opCode, unsigned short *pProgramCounter, unsigned char V[16])
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04X - SHL   V%u\n", opCode, Vx);
    // Op
    if ((V[Vx] >> 7) == 1)
        V[15] = 1;
    else
        V[15] = 0;
    V[Vx] = V[Vx] << 1;
    ++ *pProgramCounter;
}

void SNE_Vx_Vy(unsigned short const opCode, unsigned short *pProgramCounter, unsigned char V[16])
{  
    // Filter
    unsigned char Vx, Vy;
    Vx = (opCode & 0x0F00) >> 8; 
    Vy = (opCode & 0x00F0) >> 4; 
    // Print assembler code
    printf("%04X - SNE   V%u, V%u\n", opCode, Vx, Vy);
    // Op
    if (V[Vx] != V[Vy])
        *pProgramCounter += 2;
    else
        ++ *pProgramCounter;
}

void LD_I_addr(unsigned short const opCode, unsigned short *pProgramCounter, unsigned short *pI)
{
    // Filter
    unsigned short addr;
    addr = opCode & 0x0FFF;
    // Print assembler code
    printf("%04X - LD    I, #%04X\n", opCode, addr);
    // Op
    *pI = addr;
    ++ *pProgramCounter;
}

void JP_V0_addr(unsigned short const opCode, unsigned short *pProgramCounter, unsigned char V[16])
{
    // Filter
    unsigned short addr;
    addr = opCode & 0x0FFF;
    // Print assembler code
    printf("%04X - JP    V0, #%04X\n", opCode, addr);
    // Op
    *pProgramCounter = addr + V[0];
}

void RND_Vx_byte(unsigned short const opCode, unsigned short *pProgramCounter, unsigned char V[16])
{
    // Filter
    unsigned char Vx;
    unsigned short kk;
    Vx = (opCode & 0x0F00) >> 8;
    kk = opCode & 0x00FF;
    // Print assembler code
    printf("%04X - RND   V%u, #%x\n", opCode, Vx, kk);
    // Op
    unsigned short r = srand(time(NULL)) % 256;
    V[Vx] = r & kk;
    ++ *pProgramCounter;
}

void DRW_Vx_Vy_nibble(unsigned short const opCode, unsigned short * pProgramCounter, unsigned char V[16], unsigned short *pI)
{
    // Filter
    unsigned char Vx, Vy, nibble;
    Vx = (opCode & 0x0F00) >> 8;
    Vy = (opCode & 0x00F0) >> 4;
    nibble = opCode & 0x000F;
    // Print assembler code
    printf("%04X - DRW   V%u, V%u, %u\n", opCode, Vx, Vy, nibble);
    // Op
    
}

void SKP_Vx(unsigned short const opCode, unsigned short *pProgramCounter, unsigned char V[16], unsigned short keyboardState[16])
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04X - SKP   V%u\n", opCode, Vx);
    // Op
    if (keyboardState[V[Vx]])
        *pProgramCounter += 2;
    else
        ++ *programCounter;
}

void SKNP_Vx(unsigned short const opCode, unsigned short *pProgramCounter, unsigned char V[16], unsigned short keyboardState[16])
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04X - SKNP  V%u\n", opCode, Vx);
    // Op
    if (!keyboardState[V[Vx]])
        *pProgramCounter += 2;
    else
        ++ *programCounter;
}

void LD_Vx_DT(unsigned short const opCode, unsigned short *pProgramCounter, unsigned char V[16], unsigned short *pDelayTimer)
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04X - LD    V%u, DT\n", opCode, Vx);
    // Op
    V[Vx] = *pDelayTimer;
    ++ *pProgramCounter;
}

void LD_Vx_K(unsigned short const opCode, unsigned short *pProgramCounter, unsigned short keyboardState)
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04X - LD    V%u, K\n", opCode, Vx);
    // Op
    for (int i = 0; i < 16; i++) {
        if (keyboardState[i]) {
            V[Vx] = i;
            i = 16;
            ++ *pProgramCounter;
        }
    }
}

void LD_DT_Vx(unsigned short const opCode, unsigned short *pProgramCounter, unsigned char V[16], unsigned short *pDelayTimer)
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04X - LD    DT, V%u\n", opCode, Vx);
    // Op
    *pDelayTimer = V[Vx];
    ++ *pProgramCounter;
}

void LD_ST_Vx(unsigned short const opCode, unsigned short *pProgramCounter, unsigned char V[16], unsigned short *pSoundTimer)
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04X - LD    ST, V%u\n", opCode, Vx);
    // Op
    *pSoundTimer = V[Vx];
    ++ *pProgramCounter;
}

void ADD_I_Vx(unsigned short const opCode, unsigned short *pProgramCounter, unsigned char V[16], unsigned short *pI)
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04X - ADD   I, V%u\n", opCode, Vx);
    // Op
    *pI += V[Vx];
    ++ *pProgramCounter;
}

void LD_F_Vx(unsigned short const opCode, unsigned short *pProgramCounter, unsigned char V[16], unsigned short *pI)
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04X - LD    F, V%u\n", opCode, Vx);
    // Op
    *pI = V[Vx];
    ++ *pProgramCounter;
}

void LD_B_Vx(unsigned short const opCode, unsigned short *pProgramCounter, unsigned char V[16], unsigned short *pI, unsigned short memory[4096])
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04X - LD    B, V%u\n", opCode, Vx);
    // Op
    memory[I]     = V[Vx] / 100;
    memory[I + 1] = (V[Vx] / 10) % 10;
    memory[I + 2] = (V[Vx] % 100) % 10;
    ++ *pProgramCounter;
}

void LD_I_Vx(unsigned short const opCode, unsigned short *pProgramCounter, unsigned char V[16], unsigned short *pI, unsigned short memory[4096])
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04X - LD    [I], V%u\n", opCode, Vx);
    // Op
    for (int i = 0; i <= Vx) {
        memory[*pI+i] = V[i];
    }
    ++ *pProgramCounter;
}

void LD_Vx_I(unsigned short const opCode, unsigned short *pProgramCounter, unsigned char V[16], unsigned short *pI, unsigned short memory[4096])
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04X - LD    V%u, [I]\n", opCode, Vx);
    // Op
    for (int i = 0; i <= Vx) {
        V[i] = memory[*pI+i];
    }
    ++ *pProgramCounter;
}
