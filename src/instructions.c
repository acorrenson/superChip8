#include <stdio.h>
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

void SNE_Vx_Vy(unsigned short const opCode)
{  
    // Filter
    unsigned char Vx, Vy;
    Vx = (opCode & 0x0F00) >> 8; 
    Vy = (opCode & 0x00F0) >> 4; 
    // Print assembler code
    printf("%04X - SNE   V%u, V%u\n", opCode, Vx, Vy);
    // Op
    // var: programCounter, V
}

void LD_I_addr(unsigned short const opCode)
{
    // Filter
    unsigned short addr;
    addr = opCode & 0x0FFF;
    // Print assembler code
    printf("%04X - LD    I, #%04X\n", opCode, addr);
    // Op
    // var: I
}

void JP_V0_addr(unsigned short const opCode)
{
    // Filter
    unsigned short addr;
    addr = opCode & 0x0FFF;
    // Print assembler code
    printf("%04X - JP    V0, #%04X\n", opCode, addr);
    // Op
    // var: V, I
}

void RND_Vx_byte(unsigned short const opCode)
{
    // Filter
    unsigned char Vx;
    unsigned short kk;
    Vx = (opCode & 0x0F00) >> 8;
    kk = opCode & 0x00FF;
    // Print assembler code
    printf("%04X - RND   V%u, #%x\n", opCode, Vx, kk);
    // Op
    // var: random, V
}

void DRW_Vx_Vy_nibble(unsigned short const opCode)
{
    // Filter
    unsigned char Vx, Vy, nibble;
    Vx = (opCode & 0x0F00) >> 8;
    Vy = (opCode & 0x00F0) >> 4;
    nibble = opCode & 0x000F;
    // Print assembler code
    printf("%04X - DRW   V%u, V%u, %u\n", opCode, Vx, Vy, nibble);
    // Op
    // var: renderer, V, I
}

void SKP_Vx(unsigned short const opCode)
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04X - SKP   V%u\n", opCode, Vx);
    // Op
    // var: keyboard event, programCounter, V
}

void SKNP_Vx(unsigned short const opCode)
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04X - SKNP  V%u\n", opCode, Vx);
    // Op
    // var: keyboard event, programCounter, V
}

void LD_Vx_DT(unsigned short const opCode)
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04X - LD    V%u, DT\n", opCode, Vx);
    // Op
    // var: delay timer value, V
}

void LD_Vx_K(unsigned short const opCode)
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04X - LD    V%u, K\n", opCode, Vx);
    // Op
    // var: key press, V
}

void LD_DT_Vx(unsigned short const opCode)
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04X - LD    DT, V%u\n", opCode, Vx);
    // Op
    // var: delay timer, V
}

void LD_ST_Vx(unsigned short const opCode)
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04X - LD    ST, V%u\n", opCode, Vx);
    // Op
    // var: sound timer, V
}

void ADD_I_Vx(unsigned short const opCode)
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04X - ADD   I, V%u\n", opCode, Vx);
    // Op
    // var: V, I
}

void LD_F_Vx(unsigned short const opCode)
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04X - LD    F, V%u\n", opCode, Vx);
    // Op
    // var: V, I
}

void LD_B_Vx(unsigned short const opCode)
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04X - LD    B, V%u\n", opCode, Vx);
    // Op
    // var: (BCD representation ?), V, I
}

void LD_I_Vx(unsigned short const opCode)
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04X - LD    [I], V%u\n", opCode, Vx);
    // Op
    // var: V, I
}

void LD_Vx_I(unsigned short const opCode)
{
    // Filter
    unsigned char Vx;
    Vx = (opCode & 0x0F00) >> 8;
    // Print assembler code
    printf("%04X - LD    V%u, [I]\n", opCode, Vx);
    // Op
    // var: V, I
}

